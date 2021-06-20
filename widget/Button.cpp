//
// Created by fusionbolt on 2020-01-24.
//

#include "Button.h"
#include "ButtonGroup.h"

Craft::Button::Button(const std::string &text):
    AbstractButton(text)
{
}

void Craft::Button::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    renderer.RenderFillRectangle(GetGeometry(), Craft::White);
    renderer.RenderRectangle(GetGeometry(), Craft::Black);
    _text.Draw(renderer);
}

void Craft::Button::SetGeometry(Craft::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _text.SetPosition({rect.x + 10, rect.y + 10});
    _text.SetWrapLength(rect.w - 10);
    _checkedRectangle = rect;
}

void Craft::Button::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    Widget::MouseReleaseEvent(mouseEvent);
}