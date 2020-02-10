//
// Created by fusionbolt on 2020-01-24.
//

#include "Button.h"
#include "ButtonGroup.h"

GWUI::Button::Button(const std::string &text):
    AbstractButton(text)
{
}

void GWUI::Button::Draw(Renderer renderer)
{
    RendererRectangle(renderer.GetRenderer(), GetGeometry(), {255, 255, 255});
    _text.Draw(renderer);
    Widget::Draw(renderer);
}

void GWUI::Button::SetGeometry(GWUI::Rect rect) noexcept
{
    _text.SetPosition({rect.x + 10, rect.y + 10});
    _text.SetWrapLength(rect.w - 10);
    _checkedRectangle = rect;
    Widget::SetGeometry(rect);
}

void GWUI::Button::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    Widget::MouseReleaseEvent(mouseEvent);
}