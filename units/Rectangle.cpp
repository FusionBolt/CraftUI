//
// Created by fusionbolt on 2020/2/25.
//

#include "Rectangle.h"

Craft::Rectangle::Rectangle() : Rectangle(Rect{0, 0, 0, 0})
{

}

Craft::Rectangle::Rectangle(int x, int y, int w, int h) :
    Rectangle(Rect{x, y, w, h})
{
}

Craft::Rectangle::Rectangle(Craft::Rect rect):
        _rect(rect), _fillColor{232, 232, 232, 255},
        _frameColor(Craft::Black), _showFrame(true)
{
}

void Craft::Rectangle::Draw(Craft::Renderer &renderer)
{
    renderer.RenderFillRectangle(_rect, _fillColor);
    if(_showFrame)
    {
        renderer.RenderRectangle(_rect, _frameColor);
    }
}

void Craft::Rectangle::SetBackColor(Craft::Color color) noexcept
{
    _fillColor = color;
}

void Craft::Rectangle::SetFrameColor(Craft::Color color) noexcept
{
    _frameColor = color;
}

void Craft::Rectangle::SetRect(const SDL_Rect &rect) noexcept
{
    _rect = rect;
}

void Craft::Rectangle::SetShowFrame(bool show) noexcept
{
    _showFrame = show;
}

bool Craft::Rectangle::IsShowFrame() const noexcept
{
    return _showFrame;
}

Craft::Color Craft::Rectangle::GetBackColor() const noexcept
{
    return _fillColor;
}

Craft::Color Craft::Rectangle::GetFrameColor() const noexcept
{
    return _frameColor;
}

SDL_Rect Craft::Rectangle::GetRect() const noexcept
{
    return _rect;
}

Craft::Point Craft::Rectangle::GetPosition() const noexcept
{
    return {_rect.x, _rect.y};
}
