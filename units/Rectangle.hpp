//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_RECTANGLE_HPP
#define GWUI_RECTANGLE_HPP

#include "../utils/Util.hpp"

namespace GWUI
{
    class Rectangle
    {
    public:
        Rectangle(int x, int y, int w, int h) : _rect{x, y, w, h}
        {
        };

        Rectangle(Rect rect):_rect(rect){}

        Rectangle() = default;

        void Draw(Renderer renderer)
        {
            RendererRectangle(renderer.GetRenderer(), _rect, _color);
        }

        void SetColor(Color color) noexcept { _color = color; }

        void SetRect(const SDL_Rect& rect) noexcept { _rect = rect; }

        Color GetColor() const noexcept { return _color;}

        SDL_Rect GetRect() const noexcept { return _rect;}

        Point GetPosition() const noexcept {return {_rect.x, _rect.y};}

    private:
        SDL_Rect _rect{};

        Color _color = {232, 232, 232, 255};
    };
}

#endif //GWUI_RECTANGLE_HPP
