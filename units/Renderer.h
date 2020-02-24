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

    class Window;

    class Renderer
    {
    public:
        Renderer():_renderer(nullptr, SDL_DestroyRenderer){}

        void SetWindow(Window* window);

        void RenderClear();

        void RenderPresent();

        void RenderTexture(std::shared_ptr<SDL_Texture> texture, Point point);

        void RenderTexture(std::shared_ptr<SDL_Texture> texture, Rect dst, Rect src={0,0,0,0});

        void RenderClipTexture(std::shared_ptr<SDL_Texture> texture, int x, int y, Rect* clip);

        void RendererLine(Point p1, Point p2, Color color=GWUI::Black);

        void RendererRectangle(Rect rect, Color color, bool needFill = true);

        void RendererCopy(const std::shared_ptr<SDL_Texture>& texture);

        void SetRenderDrawColor(Color color);

        void ScreenShot(Rect rect) const;

        void ScreenShot() const;

        std::shared_ptr<SDL_Texture> LoadIMG(const std::string &filePath) const;

        std::shared_ptr<SDL_Texture> CreateTexture(uint32_t format, int access, int w, int h) const;

        std::shared_ptr<SDL_Texture> CreateTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const;

    private:
        void _ScreenShot(Rect rect) const;

        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>  _renderer;

        // can't create smart ptr when constructor
        Window* _window;
    };
}

#endif //GWUI_RENDERER_H
