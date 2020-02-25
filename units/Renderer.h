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

    constexpr auto Black = Color{0,0,0, 255};
    constexpr auto White = Color{255,255,255, 255};

    struct Circle
    {
    public:
        Circle(int nx, int ny, int nr):x(nx), y(ny), r(nr){}
        int x, y;
        int r;
        // TODO:uint??
    };

    struct Line
    {
    public:
        Line(Point a, Point b){}

        Point a, b;
    };

    class Window;

    class Renderer
    {
    public:
        Renderer():_renderer(nullptr, SDL_DestroyRenderer){}

        void SetWindow(Window* window);

        void RenderClear();

        void RenderPresent();

        void RenderTexture(const std::shared_ptr<SDL_Texture> &texture, Point point);

        void RenderTexture(const std::shared_ptr<SDL_Texture> &texture, Rect dst, Rect src= {0, 0, 0, 0});

        void RenderClipTexture(const std::shared_ptr<SDL_Texture> &texture, int x, int y, Rect* clip);

        void RenderLine(Point p1, Point p2, Color color= GWUI::Black);

        void RenderFillRectangle(Rect rect, Color color = GWUI::White);

        void RenderRectangle(Rect rect, Color color = GWUI::Black);

        void RenderCircle(Circle circle, Color color = GWUI::Black);

        void RenderFillCircle(Circle circle, Color color = GWUI::White);

        void RenderPoint(Point p, Color color = GWUI::Black);

        void RenderPointByNowColor(Point p);

        void RenderCopy(const std::shared_ptr<SDL_Texture>& texture);

        void SetRenderDrawColor(Color color);

        void SetRenderBlendMode(SDL_BlendMode mode);

        void ScreenShot(Rect rect) const;

        void ScreenShot() const;

        [[nodiscard]] std::shared_ptr<SDL_Texture> LoadIMG(const std::string &filePath) const;

        [[nodiscard]] std::shared_ptr<SDL_Texture> CreateTexture(uint32_t format, int access, int w, int h) const;

        [[nodiscard]] std::shared_ptr<SDL_Texture> CreateTextureFromSurface(const std::shared_ptr<SDL_Surface>& surface) const;

    private:
        void _ScreenShot(Rect rect) const;

        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>  _renderer;

        // can't create smart ptr when constructor
        Window* _window;
    };
}

#endif //GWUI_RENDERER_H
