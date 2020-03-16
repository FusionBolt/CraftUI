//
// Created by fusionbolt on 2020-01-29.
//

#include "LineEdit.h"
#include "../units/ClipBoard.h"

GWUI::LineEdit::LineEdit() : Widget()
{
    _text.SetText("Some TextUsedBeTest");
}

void GWUI::LineEdit::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    _rect.Draw(renderer);

    auto h = _text.GetTextShowHeight();
    // TODO:考虑lineWidth的范围
    // TODO:cursor render
    auto lineWidth = 10;
    auto w = _text.Draw(renderer, _cursor + 1);
    renderer.RenderLine({static_cast<int>(_geometry.x + w),
                         static_cast<int>(_geometry.y + h)},
                        {static_cast<int>(_geometry.x + w - lineWidth),
                         static_cast<int>(_geometry.y + h)}
    );

    if (_select.w != 0)
    {
        renderer.RenderRectangle(_select, GWUI::Black);
        renderer.RenderFillRectangle(_select, {100, 149, 237, 50});
    }
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
    // TODO:不完全显示的选区问题
    Widget::MousePressEvent(mouseEvent);
    auto position = mouseEvent.GetPosition();
    // set select area value
    _select.y = _geometry.y + 2; // TODO: +2 文字偏移

    _select.h = _text.GetTextShowHeight();
    _select.w = 0;

    _firstClickPosition = position;

    _selectArea.SetFirstClickPosition(position);
    _SetCursor(position.x);
}

void GWUI::LineEdit::MouseMotionEvent(const GWUI::MouseEvent &mouseEvent)
{
    Widget::MouseMotionEvent(mouseEvent);
    auto position = mouseEvent.GetPosition();
    if(JudgeCoincide(position, _geometry))
    {

    }
    // TODO:全局光标
    if (!_hadClicked)
    {
        return;
    }

    // 使用一个position记录最初单击的位置
    // select 不断更新
    auto maxX = std::max(position.x, _firstClickPosition.x);
    auto minX = std::min(position.x, _firstClickPosition.x);

    auto maxIndex = _text.GetTextIndexFromOffsetX(maxX - _geometry.x);//nIndex;
    auto minIndex = _text.GetTextIndexFromOffsetX(minX - _geometry.x);//nIndex;
    if ((minX - _geometry.x) < 0)
    {
        _cursor.Decrease();
    }
    if (minIndex == -1 || maxIndex == -1)
    {
        return;
    }
    auto space = _text.GetTextSpace(maxIndex - minIndex + 1, minIndex);

    //TOOD:max min index必须是以当前显示的内容为偏移量
    // 向前取整，取文字空间的值是到当前文字后面的位置，要框起来当前单击的文字坐标必须从文字前面开始

    // begin - min
    auto showBeginIndex = _text.GetShowTextBeginIndex();
    _select.x = static_cast<int>(std::get<0>(_text.GetTextSpace(minIndex - showBeginIndex, showBeginIndex))) + _geometry.x;
    _select.w = std::get<0>(space);

    _SetCursor(position.x);
}

void GWUI::LineEdit::MouseReleaseEvent(const GWUI::MouseEvent &mouseEvent)
{
    Widget::MouseReleaseEvent(mouseEvent);
}

void GWUI::LineEdit::KeyPressEvent(const KeyBoardEvent &keyBoardEvent)
{
#ifdef __APPLE__
    constexpr auto MainControlKey = KMOD_GUI;
#else
    constexpr auto MainControlKey = KMOD_CTRL;
#endif

    //TODO:alt delete and ctrl c, v
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
            if(_select.w == 0)
            {
                return;
            }
            auto maxIndex = _text.GetTextIndexFromOffsetX(_select.x + _select.w - _geometry.x);
            auto minIndex = _text.GetTextIndexFromOffsetX(_select.x - _geometry.x);
            std::cout << "max:" << maxIndex << " min:" << minIndex << std::endl;
            ClipBoard::SetText(_text.GetSubStr(minIndex, maxIndex - minIndex));

            _select.w = 0;
        }
        else if (pressKey == SDLK_v && SDL_GetModState() & MainControlKey)
        {
            std::cout << "get clip board" << std::endl;
            auto clipboardText = ClipBoard::GetText();
            _cursor.Increase(_text.InsertText(clipboardText, _cursor));
        }
    }
}

void GWUI::LineEdit::_SetCursor(int mouseX)
{
    auto charIndex = _text.GetTextIndexFromOffsetX(mouseX - _geometry.x);
    // TODO:int to size_t
    if (charIndex >= 0)
    {
        _cursor.SetValue(charIndex);
    }
}
