//
// Created by fusionbolt on 2020-01-29.
//

#include "LineEdit.h"

GWUI::LineEdit::LineEdit() : Widget()
{

}

void GWUI::LineEdit::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    _rect.Draw(renderer);

    auto [w, h] = _text.GetTextSpace(_cursor);

    auto lineWidth = 5;
    if(w > _geometry.w - lineWidth)
    {
        w = _text.Draw(renderer, _cursor);
    }
    else
    {
        _text.Draw(renderer);
    }
    renderer.RendererLine({static_cast<int>(_geometry.x + w),
                           static_cast<int>(_geometry.y + h)},
                                   {static_cast<int>(_geometry.x + w + lineWidth),
                                    static_cast<int>(_geometry.y + h)}
                                    );
}

void GWUI::LineEdit::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _rect.SetRect(rect);
    _text.SetPosition(_rect.GetPosition());
    _text.SetWrapLength(_geometry.w);
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
#ifdef __APPLE__
    constexpr auto MainControlKey = KMOD_GUI;
#else
    constexpr auto MainControlKey = KMOD_CTRL;
#endif

    Widget::KeyPressEvent(keyBoardEvent);
    auto event = keyBoardEvent.event;
    auto pressKey = event.key.keysym.sym;
    if(event.type == SDL_TEXTINPUT)
    {
        auto inputText = event.text.text;
        std::cout << "text input:" << inputText << std::endl;
        _cursor.Increase(_text.InsertText(inputText, _cursor));
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
        if (pressKey == SDLK_RETURN && !_editing)
        {
            // important
            SetFocus(false);
            return;
        }
        else if(pressKey == SDLK_LEFT)
        {
            _cursor.Decrease();
        }
        else if(pressKey == SDLK_RIGHT)
        {
            _cursor.Increase(1, _text.GetTextSize());
        }
            // short cut
        else if ((pressKey == SDLK_BACKSPACE || pressKey == SDLK_DELETE) && !_text.IsEmpty())
        {
            if (SDL_GetModState() & MainControlKey)
            {
                _text.ClearText();
                _cursor.Reset();
            }
            else if(SDL_GetModState() & KMOD_ALT)
            {
                _cursor.Decrease(_text.EraseFrontWord(_cursor));
            }
            else
            {
                if(_cursor != 0)
                {
                    _cursor.Decrease();
                    _text.EraseStr(_cursor, 1);
                }
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
            auto clipboardText = GetClipboardText();
            _cursor.Increase(_text.InsertText(clipboardText, _cursor));
        }
    }
}
