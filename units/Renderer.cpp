//
// Created by fusionbolt on 2020/2/19.
//

#include "Renderer.h"
#include "SDL_image.h"
#include "../widget/Window.h"

void GWUI::Renderer::SetWindow(Window* window)
{
    _renderer.reset(SDL_CreateRenderer(window->_window.get(), -1, SDL_RENDERER_ACCELERATED));
    _window = window;
    SetRenderBlendMode(SDL_BLENDMODE_BLEND);
}

void GWUI::Renderer::RenderClear()
{
    SDL_RenderClear(_renderer.get());
}

void GWUI::Renderer::RenderPresent()
{
    SDL_RenderPresent(_renderer.get());
}

void GWUI::Renderer::RenderTexture(const std::shared_ptr<SDL_Texture> &texture, Point point)
{
    Rect dst;
    dst.x = point.x;
    dst.y = point.y;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(_renderer.get(), texture.get(), nullptr, &dst);
}

void GWUI::Renderer::RenderTexture(const std::shared_ptr<SDL_Texture> &texture, Rect dst, Rect src)
{
    // TODO:query src的值 以及clip
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(_renderer.get(), texture.get(), &src, &dst);
}

void GWUI::Renderer::RenderClipTexture(const std::shared_ptr<SDL_Texture> &texture, int x, int y, GWUI::Rect* clip)
{
    SDL_Rect renderQuad = { x, y, clip->w, clip->h };

    //Set clip rendering dimensions
    if(clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(_renderer.get(), texture.get(), nullptr, &renderQuad );
}

// TODO:
// 所有的样式类型类，模板或者继承
// Rect recode position value
// Rectangle draw and set style

void GWUI::Renderer::RenderPoint(GWUI::Point p, GWUI::Color color)
{
    SetRenderDrawColor(color);
    SDL_RenderDrawPoint(_renderer.get(), p.x, p.y);
}

void GWUI::Renderer::RenderLine(Point p1, Point p2, Color color)
{
    SetRenderDrawColor(color);
    SDL_RenderDrawLine(_renderer.get(), p1.x, p1.y, p2.x, p2.y);
}

void GWUI::Renderer::RenderRectangle(Rect rect, Color color)
{
    SetRenderDrawColor(color);
    SDL_RenderDrawRect(_renderer.get(), &rect);
}

void GWUI::Renderer::RenderFillRectangle(GWUI::Rect rect, Color color)
{
    SetRenderDrawColor(color);
    SDL_RenderFillRect(_renderer.get(), &rect);
}

std::shared_ptr<SDL_Texture> GWUI::Renderer::LoadIMG(const std::string &filePath) const
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer.get(), filePath.c_str());
    if (texture == nullptr)
    {
        ERROR_INFO("load texture\n");
        SDL_GetError();
    }
    return std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
}

void GWUI::Renderer::SetRenderDrawColor(GWUI::Color color)
{
    SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
}

std::shared_ptr<SDL_Texture> GWUI::Renderer::CreateTexture(uint32_t format, int access, int w, int h) const
{
    return std::shared_ptr<SDL_Texture>(SDL_CreateTexture(_renderer.get(),
            format, access, w, h), SDL_DestroyTexture);
}

void GWUI::Renderer::RenderCopy(const std::shared_ptr<SDL_Texture>& texture)
{
    SDL_RenderCopy(_renderer.get(), texture.get(), nullptr, nullptr);
}

std::shared_ptr<SDL_Texture> GWUI::Renderer::CreateTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const
{
    return std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(_renderer.get(), surface.get()),
            SDL_DestroyTexture);
}

void GWUI::Renderer::ScreenShot(Rect rect) const
{
    _ScreenShot(rect);
}

void GWUI::Renderer::ScreenShot() const
{
    auto [w, h] = _window->GetWindowSize();
    _ScreenShot({0, 0, w, h});
}

void GWUI::Renderer::_ScreenShot(Rect rect) const
{
    std::shared_ptr<SDL_Surface> screenShot(
            SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000),
            SDL_FreeSurface);
    SDL_RenderReadPixels(_renderer.get(), &rect, SDL_PIXELFORMAT_ARGB8888, screenShot->pixels, screenShot->pitch);
    SDL_SaveBMP(screenShot.get(), "screenshot.bmp");
    // TODO:screenshot name

    // about screenshot
    // https://stackoverflow.com/questions/22315980/sdl2-c-taking-a-screenshot
}

void GWUI::Renderer::RenderCircle(Circle circle, Color color)
{
    // about RenderCircle and RenderFillCircle
    // https://gist.github.com/derofim/912cfc9161269336f722

    auto radius = circle.r;
    auto error = static_cast<double>(-radius);
    auto x = static_cast<double>(radius)- 0.5;
    double y = 0.5;
    auto cx = static_cast<double>(circle.x) - 0.5;
    auto cy = static_cast<double>(circle.y) - 0.5;

    SetRenderDrawColor(color);
    while (x >= y)
    {
        RenderPointByNowColor({static_cast<int>(cx + x), static_cast<int>(cy + y)});
        RenderPointByNowColor({static_cast<int>(cx + y), static_cast<int>(cy + x)});

        if (x != 0)
        {
            RenderPointByNowColor({static_cast<int>(cx - x), static_cast<int>(cy + y)});
            RenderPointByNowColor({static_cast<int>(cx + y), static_cast<int>(cy - x)});
        }

        if (y != 0)
        {
            RenderPointByNowColor({static_cast<int>(cx + x), static_cast<int>(cy - y)});
            RenderPointByNowColor({static_cast<int>(cx - y), static_cast<int>(cy + x)});
        }

        if (x != 0 && y != 0)
        {
            RenderPointByNowColor({static_cast<int>(cx - x), static_cast<int>(cy - y)});
            RenderPointByNowColor({static_cast<int>(cx - y), static_cast<int>(cy - x)});
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
        /*
        // sleep for debug
        SDL_RenderPresent(gRenderer);
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        */
    }
}

void GWUI::Renderer::RenderFillCircle(Circle circle, GWUI::Color color)
{
    // Note that there is more to altering the bitrate of this
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;

    //double ra = (double)radius;

    auto radius = circle.r;
    auto circleX = circle.x;
    auto circleY = circle.y;
    for (int y = 1; y <= radius; y += 1)
    {
        // This loop is unrolled a bit, only iterating through half of the
        // height of the circle.  The result is used to draw a scan line and
        // its mirror image below it.

        // The following formula has been simplified from our original.  We
        // are using half of the width of the circle because we are provided
        // with a center and we need left/right coordinates.

        //double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        // int x = p.x - dx;

        // double y
        auto dy = static_cast<double>(y);
        auto dx = static_cast<int>(floor(sqrt((2.0 * radius * dy) - (dy * dy))));
        RenderLine({circleX - dx, circleY + y - radius},
                   {circleX + dx, circleY + y - radius}, color);
        RenderLine({circleX - dx, circleY - y + radius},
                   {circleX + dx, circleY - y + radius}, color);

        // Grab a pointer to the left-most pixel for each half of the circle
        /*Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(circleY + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(circleY - r + dy)) * surface->pitch + x * BPP;
        for (; x <= circleX + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }*/
        /*
        // sleep for debug
        SDL_RenderPresent(gRenderer);
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
        */
    }
}

void GWUI::Renderer::SetRenderBlendMode(SDL_BlendMode mode)
{
    // SDL_BLENDMODE_NONE
    // SDL_BLENDMODE_BLEND
    SDL_SetRenderDrawBlendMode(_renderer.get(), mode);
}

void GWUI::Renderer::RenderPointByNowColor(GWUI::Point p)
{
    SDL_RenderDrawPoint(_renderer.get(), p.x, p.y);
}
