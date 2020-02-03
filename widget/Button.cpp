//
// Created by fusionbolt on 2020-01-24.
//

#include "Button.h"

#include <utility>

GWUI::Button::Button(GWUI::Rect rect, Widget::Ptr parent, const std::string &text):
_rect(rect), _text(text, 30), Widget(parent)
{
    _text.SetPosition({rect.x + 10, rect.y + 10});
}

void GWUI::Button::Draw(Renderer renderer)
{
    _rect.Draw(renderer);
    _text.Draw(renderer);
    Widget::Draw(renderer);
}

std::string GWUI::Button::GetText()
{
    return _text.GetText();
}

void GWUI::Button::SetText(const std::string &text)
{
    _text.SetText(text);
}

GWUI::Button::Button(GWUI::Widget::Ptr parent, const std::string& text):Widget(parent),
    _rect(Rect{100,100,200,100}), _text(text, 30)
{
    auto rect = _rect.GetRect();
    _text.SetPosition({rect.x + 10, rect.y + 10});
}

void GWUI::Button::OnClicked(std::function<void()> f)
{
    _onClicked = std::move(f);
}

void GWUI::Button::SetGeometry(GWUI::Rect rect) noexcept
{
    _rect = rect;
    _text.SetPosition({rect.x + 10, rect.y + 10});
    Widget::SetGeometry(rect);
}

void GWUI::Button::MousePressEvent(const MouseEvent &mouseEvent)
{
    _rect.SetColor({0, 0, 232});
    _click = true;
    if(_onClicked != nullptr)
    {
        std::invoke(_onClicked);
    }
    Widget::MousePressEvent(mouseEvent);
}

void GWUI::Button::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    if(_click)
    {
        _rect.SetColor({0, 200, 0});
    }
    Widget::MouseReleaseEvent(mouseEvent);
}