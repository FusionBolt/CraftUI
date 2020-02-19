//
// Created by fusionbolt on 2020/2/19.
//

#include "Renderer.h"
#include "SDL_image.h"

void GWUI::Renderer::SetWindow(SDL_Window *window)
{
    _renderer.reset(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED),
                    SDL_DestroyRenderer);
}

void GWUI::Renderer::RenderClear()
{
    SDL_RenderClear(_renderer.get());
}

void GWUI::Renderer::RenderPresent()
{
    SDL_RenderPresent(_renderer.get());
}

SDL_Renderer* GWUI::Renderer::GetRenderer() const
{
    return _renderer.get();
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

std::shared_ptr<SDL_Texture> GWUI::Renderer::LoadIMG(const std::string &filePath)
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

