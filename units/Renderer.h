//
// Created by fusionbolt on 2020-01-26.
//

#ifndef GWUI_RENDERER_H
#define GWUI_RENDERER_H

#include <memory>
#include "SDL_render.h"
#include "../utils/Util.hpp"

namespace GWUI
{
    using Color = SDL_Color;

    using Rect = SDL_Rect;

    constexpr auto Black = Color{0,0,0};
    constexpr auto White = Color{255,255,255};

    class Renderer
    {
    public:
        Renderer():_renderer(nullptr, SDL_DestroyRenderer){}

        void SetWindow(SDL_Window* window);

        void RenderClear();

        void RenderPresent();

        SDL_Renderer* GetRenderer() const;

        void RenderTexture(std::shared_ptr<SDL_Texture> texture, Point point);

        void RenderTexture(std::shared_ptr<SDL_Texture> texture, Rect dst, Rect src={0,0,0,0});

        void RendererLine(Point p1, Point p2, Color color=GWUI::Black);

        void RendererRectangle(Rect rect, Color color, bool needFill = true);

        std::shared_ptr<SDL_Texture> LoadIMG(const std::string &filePath);

        void SetRenderDrawColor(Color color);

    private:
        std::shared_ptr<SDL_Renderer>  _renderer;
    };
}

#endif //GWUI_RENDERER_H
