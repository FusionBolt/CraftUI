//
// Created by fusionbolt on 2020/2/19.
//

#include "Renderer.h"
#include "SDL_image.h"
#include "../widget/Window.h"

void GWUI::Renderer::SetWindow(Window* window)
{
    _renderer.reset(SDL_CreateRenderer(window->_window.get(), -1, SDL_RENDERER_ACCELERATED),
                    SDL_DestroyRenderer);
    _window = window;
}

void GWUI::Renderer::RenderClear()
{
    SDL_RenderClear(_renderer.get());
}

void GWUI::Renderer::RenderPresent()
{
    SDL_RenderPresent(_renderer.get());
}

void GWUI::Renderer::RenderTexture(std::shared_ptr<SDL_Texture> texture, Point point)
{
    Rect dst;
    dst.x = point.x;
    dst.y = point.y;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(_renderer.get(), texture.get(), nullptr, &dst);
}

void GWUI::Renderer::RenderTexture(std::shared_ptr<SDL_Texture> texture, Rect dst, Rect src)
{
//        SDL_Rect dst;
//        dst.x = x;
//        dst.y = y;
//        dst.w = w;
//        dst.h = h;
//        SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
//        SDL_RenderCopy(render, texture, nullptr, &dst);
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(_renderer.get(), texture.get(), &src, &dst);
}

void GWUI::Renderer::RendererLine(Point p1, Point p2, Color color)
{
    SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(_renderer.get(), p1.x, p1.y, p2.x, p2.y);
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
}

void GWUI::Renderer::RendererRectangle(Rect rect, Color color, bool needFill)
{
    SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, 255);
    if(needFill)
    {
        SDL_RenderFillRect(_renderer.get(), &rect);
    }
    SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255);
    SDL_RenderDrawRect(_renderer.get(), &rect);
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

void GWUI::Renderer::RendererCopy(const std::shared_ptr<SDL_Texture>& texture)
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

