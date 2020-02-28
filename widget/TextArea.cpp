//
// Created by fusionbolt on 2020-01-25.
//

#include "TextArea.h"

GWUI::TextArea::TextArea(GWUI::Rect rect):
        Widget(), _rectangle(rect),
        _text("this is a TextArea\nauto break line by word", 30, {255, 255, 255, 255}, rect.w)
{
    _text.SetPosition(Point{rect.x, rect.y});
    _text.SetAutoBreakLine(true);
    _rectangle.SetBackColor({128, 128, 128, 255});
}

void GWUI::TextArea::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    _rectangle.Draw(renderer);
    _text.Draw(renderer);
}

void GWUI::TextArea::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _rectangle = rect;
    _text.SetPosition(Point{rect.x, rect.y});
    _rectangle.SetBackColor({128, 128, 128, 255});
    _text.SetWrapLength(rect.w);
}

void GWUI::TextArea::KeyPressEvent(const KeyBoardEvent &keyBoardEvent)
{
#ifdef __APPLE__
    constexpr auto MainControlKey = KMOD_GUI;
#else
    constexpr auto MainControlKey = KMOD_CTRL;
#endif

    auto [w1, h1] = _text.GetTextSpace(_text.GetTextSize());
    std::cout << "size text w:" << w1 << " h:" << h1 << std::endl;
    auto [w2, h2] = _text.GetUTF8TextSpace(_text.GetTextSize());
    std::cout << "size text w:" << w2 << " h:" << h2 << std::endl;

    Widget::KeyPressEvent(keyBoardEvent);
    auto event = keyBoardEvent.event;
    auto pressKey = event.key.keysym.sym;
    if (event.type == SDL_TEXTINPUT)
    {
        auto inputText = event.text.text;
        std::cout << "text input:" << inputText << std::endl;
        _text.InsertTextBack(inputText);
        _editing = false;
    }
    else if (event.type == SDL_TEXTEDITING)
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
    else if (event.type == SDL_KEYDOWN)
    {
        std::cout << "key down" << std::endl;
        if (pressKey == SDLK_RETURN && !_editing)
        {
            _text.InsertChar('\n');
        }
        // short cut
        else if ((pressKey == SDLK_BACKSPACE || pressKey == SDLK_DELETE) && !_text.IsEmpty())
        {
            if (SDL_GetModState() & MainControlKey)
            {
                _text.PopBackLine();
            }
            else if (SDL_GetModState() & KMOD_ALT)
            {
                _text.EraseFrontWord(_text.GetTextSize());
            }
            else
            {
                _text.PopBackChar();
            }
        }
        else if (pressKey == SDLK_c && SDL_GetModState() & MainControlKey)
        {
            std::cout << "set clip board" << std::endl;
            SetClipboardText("clip");
        }
        else if (pressKey == SDLK_v && SDL_GetModState() & MainControlKey)
        {
            std::cout << "get clip board" << std::endl;
            _text.InsertTextBack(GetClipboardText());
        }
    }
}

void GWUI::TextArea::SetText(std::string text)
{
    _text.SetText(std::move(text));
}

void GWUI::TextArea::MousePressEvent(const GWUI::MouseEvent &mouseEvent)
{
    Widget::MousePressEvent(mouseEvent);
    auto event = mouseEvent.GetEvent();
    if (event.button.clicks == 2)
    {
        SetClipboardText(_text.GetText());
    }
}

void GWUI::TextArea::SetReadOnly(bool isReadOnly)
{
    _readOnly = isReadOnly;
}

bool GWUI::TextArea::IsReadOnly()
{
    return _readOnly;
}
