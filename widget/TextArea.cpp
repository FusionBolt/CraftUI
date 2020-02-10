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
    auto pressKey = event.key.keysym.sym;
    if(event.type == SDL_TEXTINPUT)
    {
        auto inputText = event.text.text;
        std::cout << "text input:" << inputText << std::endl;
        _text.AppendStr(inputText);
        _editing = false;
    }
    else if(event.type == SDL_TEXTEDITING)
    {
        _editing = true;
        std::cout << "text editing" << std::endl;
        auto composition = event.edit.text;
        auto cursor = event.edit.start;
        auto selection_len = event.edit.length;
        std::cout << "composition:" << composition << std::endl;
        std::cout << "cursor:" << cursor << std::endl;
        std::cout << "selection_len:" << selection_len << std::endl;
    }
    else if(event.type == SDL_KEYDOWN)
    {
        std::cout << "key down" << std::endl;
        if (pressKey == SDLK_BACKSPACE && !_text.IsEmpty())
        {
            // TODO: different OS  shortcut key
            if (SDL_GetModState() & KMOD_GUI)
            {
                _text.ClearText();
                // TODO: clear line or all text
                // TODO: clear word
            }
            else
            {
                _text.PopBackChar();
            }
        }
        else if (pressKey == SDLK_c && SDL_GetModState() & KMOD_GUI)
        {
            std::cout << "set clip board" << std::endl;
            SetClipboardText("clip");
        }
        else if (pressKey == SDLK_v && SDL_GetModState() & KMOD_GUI)
        {
            std::cout << "get clip board" << std::endl;
            _text.AppendStr(GetClipboardText());
        }
        else if (pressKey == SDLK_RETURN && !_editing)
        {
            _text.AppendChar('\n');
        }
    }
    Widget::KeyPressEvent(keyBoardEvent);
}

void GWUI::TextArea::SetText(std::string text)
{
    _text.SetText(std::move(text));
}

void GWUI::TextArea::MousePressEvent(const GWUI::MouseEvent &mouseEvent)
{
    auto event = mouseEvent.GetEvent();
    if(event.button.clicks == 2)
    {
        SetClipboardText(_text.GetText());
    }
    Widget::MousePressEvent(mouseEvent);
}
