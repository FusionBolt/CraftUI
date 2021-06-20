//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_RECTANGLE_H
#define GWUI_RECTANGLE_H

#include "Renderer.h"

namespace Craft
{
    class Rectangle
    {
    public:
        Rectangle();

        Rectangle(int x, int y, int w, int h);

        Rectangle(Rect rect);

        void Draw(Renderer& renderer);

        void SetBackColor(Color color) noexcept;

        void SetFrameColor(Color color) noexcept;

        void SetRect(const SDL_Rect& rect) noexcept;

        void SetShowFrame(bool show) noexcept;

        [[nodiscard]] bool IsShowFrame() const noexcept;

        [[nodiscard]] Color GetBackColor() const noexcept;

        [[nodiscard]] Color GetFrameColor() const noexcept;

        [[nodiscard]] SDL_Rect GetRect() const noexcept;

        [[nodiscard]] Point GetPosition() const noexcept;

    private:
        SDL_Rect _rect{};

        Color _fillColor;

        Color _frameColor;

        bool _showFrame;
    };
}

#endif //GWUI_RECTANGLE_H
