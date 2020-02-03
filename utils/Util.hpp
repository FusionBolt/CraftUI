//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_UTIL_HPP
#define GWUI_UTIL_HPP

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "../units/Renderer.hpp"

#define ERROR_INFO(errorInfo) std::cout << \
"error file:" << __FILE__ << std::endl << \
"Line:" << __LINE__ << std::endl <<\
 "function: "<< __FUNCTION__ << std::endl << \
errorInfo

namespace GWUI
{
    using Color = SDL_Color;

    using Rect = SDL_Rect;

    using CrudeEvent = SDL_Event;

    struct Point
    {
        int x, y;
    };

    inline SDL_Texture *LoadIMG(const std::string &filePath, std::shared_ptr<SDL_Renderer> render)
    {
        SDL_Texture *texture = IMG_LoadTexture(render.get(), filePath.c_str());
        if (texture == nullptr)
        {
            ERROR_INFO("load texture\n");
            SDL_GetError();
        }
        return texture;
    }

    inline void RenderTexture(std::shared_ptr<SDL_Texture> texture, std::shared_ptr<SDL_Renderer> render, Point point)
    {
        Rect dst;
        dst.x = point.x;
        dst.y = point.y;
        SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
        SDL_RenderCopy(render.get(), texture.get(), nullptr, &dst);
    }

    inline void RenderTexture(std::shared_ptr<SDL_Texture> texture, std::shared_ptr<SDL_Renderer> render, Rect dst, Rect src={0,0,0,0})
    {
//        SDL_Rect dst;
//        dst.x = x;
//        dst.y = y;
//        dst.w = w;
//        dst.h = h;
//        SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
//        SDL_RenderCopy(render, texture, nullptr, &dst);
        SDL_QueryTexture(texture.get(), nullptr, nullptr, &src.w, &src.h);
        SDL_RenderCopy(render.get(), texture.get(), &src, &dst);
    }

    inline void RendererLine(std::shared_ptr<SDL_Renderer> renderer, Point p1, Point p2, Color color={255, 255, 255, 255})
    {
        SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, 255);
        SDL_RenderDrawLine(renderer.get(), p1.x, p1.y, p2.x, p2.y);
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    }

    inline void RendererRectangle(std::shared_ptr<SDL_Renderer> renderer, Rect rect, Color color, bool needFill = true)
    {
        SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, 255);
        if(needFill)
        {
            SDL_RenderFillRect(renderer.get(), &rect);
        }
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer.get(), &rect);
    }

    inline bool JudgeCoincide(Point mousePosition, SDL_Rect rect)
    {
        auto mouseX = mousePosition.x;
        auto mouseY = mousePosition.y;
        //std::cout << mouseX << " " << mouseY << std::endl;
        //std::cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << std::endl;
        if (mouseX > rect.x && mouseX < rect.x + rect.w)
        {
            if (mouseY > rect.y && mouseY < rect.y + rect.h)
            {
                return true;
            }
        }
        return false;
    }

}


#endif //GWUI_UTIL_HPP
