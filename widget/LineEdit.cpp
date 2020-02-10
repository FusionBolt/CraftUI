//
// Created by fusionbolt on 2020-01-29.
//

#include "LineEdit.h"

GWUI::LineEdit::LineEdit() : Widget()
{

}

void GWUI::LineEdit::Draw(GWUI::Renderer renderer)
{
    Widget::Draw(renderer);
    _rect.Draw(renderer);
    _text.Draw(renderer);
}

void GWUI::LineEdit::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _rect.SetRect(rect);
    _text.SetPosition(_rect.GetPosition());
}

void GWUI::LineEdit::KeyReleaseEvent(const KeyBoardEvent &keyBoardEvent)
{
    Widget::KeyReleaseEvent(keyBoardEvent);
}

void GWUI::LineEdit::MousePressEvent(const MouseEvent &mouseEvent)
{
    Widget::MousePressEvent(mouseEvent);
}

void GWUI::LineEdit::KeyPressEvent(const KeyBoardEvent &keyBoardEvent)
{
    Widget::KeyPressEvent(keyBoardEvent);
    auto event = keyBoardEvent.event;
    auto input = event.key.keysym.sym;
    if(input == SDLK_BACKSPACE)
    {
        _text.PopBackChar();
    }
    else if(input == SDLK_SPACE)
    {
        _text.AppendChar(' ');
    }
    else
    {
        auto keyName = std::string(SDL_GetKeyName(event.key.keysym.sym));
        std::cout << "input:" << keyName << std::endl;
        if(keyName.size() > 1)
        {
            std::cout << "size > 1" << std::endl;
        }
        _text.AppendChar(keyName[0]);
    }
}
