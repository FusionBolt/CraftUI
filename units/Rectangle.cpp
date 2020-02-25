//
// Created by fusionbolt on 2020/2/25.
//

#include "Rectangle.h"

GWUI::Rectangle::Rectangle() : Rectangle(Rect{0,0,0,0})
{

}

GWUI::Rectangle::Rectangle(int x, int y, int w, int h) :
    Rectangle(Rect{x, y, w, h})
{
}

GWUI::Rectangle::Rectangle(GWUI::Rect rect):
    _rect(rect),_fillColor{232, 232, 232, 255},
    _frameColor(GWUI::Black), _showFrame(true)
{
}

void GWUI::Rectangle::Draw(GWUI::Renderer &renderer)
{
    renderer.RenderFillRectangle(_rect, _fillColor);
    if(_showFrame)
    {
        renderer.RenderRectangle(_rect, _frameColor);
    }
}

void GWUI::Rectangle::SetBackColor(GWUI::Color color) noexcept
{
    _fillColor = color;
}

void GWUI::Rectangle::SetFrameColor(GWUI::Color color) noexcept
{
    _frameColor = color;
}

void GWUI::Rectangle::SetRect(const SDL_Rect &rect) noexcept
{
    _rect = rect;
}

void GWUI::Rectangle::SetShowFrame(bool show) noexcept
{
    _showFrame = show;
}

bool GWUI::Rectangle::IsShowFrame() const noexcept
{
    return _showFrame;
}

GWUI::Color GWUI::Rectangle::GetBackColor() const noexcept
{
    return _fillColor;
}

GWUI::Color GWUI::Rectangle::GetFrameColor() const noexcept
{
    return _frameColor;
}

SDL_Rect GWUI::Rectangle::GetRect() const noexcept
{
    return _rect;
}

GWUI::Point GWUI::Rectangle::GetPosition() const noexcept
{
    return {_rect.x, _rect.y};
}
