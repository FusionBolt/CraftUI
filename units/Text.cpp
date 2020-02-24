//
// Created by fusionbolt on 2020-01-24.
//

#include "Text.h"

GWUI::Text::Text(std::string text, uint16_t size, const GWUI::Color &color, uint32_t wrapLength):
        _text(std::move(text)), _color(color), _fontSize(size), _font(size),
        _wrapLength(wrapLength)
{
    //_ResetTexture();
    _position = Point{20, 20};
}

// EndPosition is point to lastChar + 1
int GWUI::Text::Draw(Renderer& renderer, int textEndPosition)
{
    if (_dirty)
    {
        _ResetTexture(renderer);
        _dirty = false;
    }
    auto space = _AdjustTextureArea(renderer, textEndPosition);
    renderer.RenderTexture(_texture, _position);
    return space;
}

void GWUI::Text::_ResetTexture(Renderer& renderer)
{
    auto ttf = _font.RenderTextBlendedWrapped(_text, _color, _wrapLength);
    // TODO:限定文字渲染范围
    Uint16 text[] = {0x4F60, 0x597D, 0};
    // auto ttf = TTF_RenderUNICODE_Blended_Wrapped(_font.GetFontPtr(), text, _color, _wrapLength);
    _texture = renderer.CreateTextureFromSurface(ttf);
}

void GWUI::Text::SetPosition(Point position) noexcept
{
    _position = position;
    _dirty = true;
}

void GWUI::Text::PopBackChar()
{
    _text.pop_back();
    _dirty = true;
}

void GWUI::Text::InsertChar(char c)
{
    _text.append({c});
    _dirty = true;
}

void GWUI::Text::SetColor(GWUI::Color color) noexcept
{
    _color = color;
    _dirty = true;
}

void GWUI::Text::SetWrapLength(uint32_t wrapLength) noexcept
{
    _wrapLength = wrapLength;
    _dirty = true;
}

void GWUI::Text::SetText(std::string text)
{
    _text = std::move(text);
    _dirty = true;
}

void GWUI::Text::SetFontSize(uint16_t size) noexcept
{
    _font.SetSize(size);
    _dirty = true;
}

std::string GWUI::Text::GetText() const noexcept
{
    return _text;
}

GWUI::Color GWUI::Text::GetFontColor() const noexcept
{
    return _color;
}

size_t GWUI::Text::InsertText(const std::string &s, size_t pos)
{
    _text.insert(pos, s);
    _dirty = true;
    return s.size();
}

size_t GWUI::Text::InsertTextBack(const std::string &s)
{
    _text.insert(_text.size() - 1, s);
    _dirty = true;
    return s.size();
}

bool GWUI::Text::IsEmpty() const noexcept
{
    return _text.empty();
}

void GWUI::Text::ClearText()
{
    _text.clear();
    _dirty = true;
}

// size is point to last char + 1
size_t GWUI::Text::EraseFrontWord(size_t wordEndPosition)
{
    if(wordEndPosition == 0)
    {
        return 0;
    }
    auto [wordStartIndex, wordSize] = _FindFrontWordStartIndex(wordEndPosition - 1, _text);
    _text.erase(wordStartIndex, wordSize);
    _dirty = true;
    return wordSize;
}

size_t GWUI::Text::PopBackLine()
{
    size_t lineSize = 0;
    auto index = _text.find_last_of('\n');
    if(index != std::string::npos)
    {
        lineSize = _text.size() - index;
        _text.erase(index, lineSize);
    }
    else
    {
        _text.clear();
    }
    _dirty = true;
    return lineSize;
}

bool GWUI::Text::_IsSpacer(char c) const noexcept
{
    return c == ' ' || c == '\n' || c == '\t';
}

size_t GWUI::Text::GetTextSize() const noexcept
{
    return _text.size();
}

std::tuple<size_t, size_t> GWUI::Text::GetTextSpace(size_t length) const
{
    return _font.GetTextSpace(_text.substr(0, length));
}

std::tuple<size_t, size_t> GWUI::Text::GetUTF8TextSpace(size_t length) const
{
    return _font.GetUTF8TextSpace(_text.substr(0, length));
}

void GWUI::Text::EraseStr(size_t pos, size_t length)
{
    _text.erase(pos, length);
    _dirty = true;
}

// base index is point to last char
// not point to last char + 1
std::tuple<size_t, size_t> GWUI::Text::_FindFrontWordStartIndex(size_t baseIndex, const std::string& text)
{
    // TODO:baseIndex > text.size()
    // 字符串操作都是类似问题
    size_t wordSize = 0;
    int wordStartIndex = baseIndex, lastCharIndex = baseIndex;
    for(;lastCharIndex >= 0; --lastCharIndex)
    {
        if(text[lastCharIndex] != ' ')
        {
            wordStartIndex = lastCharIndex - 1;
            for(;wordStartIndex >= 0; --wordStartIndex)
            {
                if(_IsSpacer(text[wordStartIndex]))
                {
                    wordSize = baseIndex + 1 - wordStartIndex;
                    break;
                }
            }
            if(wordStartIndex == -1)
            {
                wordSize = baseIndex + 1;
                wordStartIndex = 0;
            }
            break;
        }
    }
    if(lastCharIndex == -1)
    {
        wordSize = baseIndex + 1;
        wordStartIndex = 0;
    }
    return std::make_tuple(wordStartIndex, wordSize);
}

size_t GWUI::Text::_AdjustTextureArea(const Renderer& renderer, int textEndPosition)
{
    size_t space = 0;
    for(auto textBeginIndex = 0; textBeginIndex < textEndPosition; ++textBeginIndex)
    {
        space = std::get<0>(_font.GetTextSpace(_text.substr(textBeginIndex, textEndPosition - textBeginIndex)));
        if(space <= _wrapLength - 5)
        {
            auto ttf = _font.RenderTextBlendedWrapped(_text, _color, _wrapLength, textBeginIndex);
            _texture = renderer.CreateTextureFromSurface(ttf);
            break;
        }
    }
    return space;
}