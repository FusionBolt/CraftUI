//
// Created by fusionbolt on 2020-01-25.
//

#include "TextArea.h"

GWUI::TextArea::TextArea(GWUI::Rect rect):
        Widget(), _rectangle(rect),
        _text("this is a TextArea\nauto break line by word", 30, {255, 255, 255}, rect.w)
{
    _text.SetPosition(Point{rect.x, rect.y});
    _rectangle.SetColor({128, 128, 128});
}

void GWUI::TextArea::Draw(Renderer renderer)
{
    _rectangle.Draw(renderer);
    _text.Draw(renderer);
    Widget::Draw(renderer);
}

void GWUI::TextArea::SetGeometry(GWUI::Rect rect) noexcept
{
    _rectangle = rect;
    _text.SetPosition(Point{rect.x, rect.y});
    _rectangle.SetColor({128, 128, 128});
    _text.SetWrapLength(rect.w);
    Widget::SetGeometry(rect);
}

void GWUI::TextArea::KeyPressEvent(const KeyBoardEvent &keyBoardEvent)
{
    auto event = keyBoardEvent.event;
    auto input = event.key.keysym.sym;
    if(input == SDLK_BACKSPACE)
    {
        _text.PopBackChar();
    }
    else if(input == SDLK_CAPSLOCK)
    {
        _capsOpen = !_capsOpen;
    }
    else if(input == SDLK_SPACE)
    {
        _text.AppendChar(' ');
    }
    else if(input == SDLK_KP_ENTER || input == SDLK_RETURN)
    {
        _text.AppendChar('\n');
    }
    else
    {
        auto keyName = std::string(SDL_GetKeyName(event.key.keysym.sym));
        if(!_capsOpen)
        {
            std::transform(keyName.begin(), keyName.end(), keyName.begin(), ::towlower);
        }
        std::cout << "input:" << keyName << std::endl;
        if(keyName.size() > 1)
        {
            std::cout << "size > 1" << std::endl;
        }
        _text.AppendChar(keyName[0]);
    }
    Widget::KeyPressEvent(keyBoardEvent);
}

