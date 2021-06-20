//
// Created by fusionbolt on 2020-01-24.
//

#include "Text.h"

Craft::Text::Text(std::string text, uint16_t size, const Craft::Color &color, uint32_t wrapLength):
        _text(std::move(text)), _color(color), _fontSize(size), _font(size),
        _wrapLength(wrapLength), _showTextBeginIndex(0),
        _dirty(false), _autoBreakLine(true)
{
    //_ResetTexture();
    _position = Point{20, 20};
}

// EndPosition is point to lastChar + 1
int Craft::Text::Draw(Renderer& renderer, int textEndPosition)
{
    if (_dirty)
    {
        _ResetTexture(renderer);
        _dirty = false;
    }
    auto space = _AdjustShowTextureWidth(renderer, textEndPosition);
    renderer.RenderTexture(_texture, _position);
    return space;
}

void Craft::Text::_ResetTexture(const Renderer& renderer, size_t offset)
{
    std::shared_ptr<SDL_Surface> ttf;
    if (_autoBreakLine)
    {
        ttf = _font.RenderTextBlendedWrapped(_text, _color, _wrapLength);
    }
    else
    {
        ttf = _font.RenderTextBlended(_text, _color);
    }
    Uint16 text[] = {0x4F60, 0x597D, 0};
    // auto ttf = TTF_RenderUNICODE_Blended_Wrapped(_font.GetFontPtr(), text, _fillColor, _wrapLength);
    _texture = renderer.CreateTextureFromSurface(ttf);
}

void Craft::Text::SetPosition(Point position) noexcept
{
    _position = position;
    _dirty = true;
}

void Craft::Text::PopBackChar()
{
    _text.pop_back();
    _dirty = true;
}

void Craft::Text::InsertChar(char c)
{
    _text.append({c});
    _dirty = true;
}

void Craft::Text::SetColor(Craft::Color color) noexcept
{
    _color = color;
    _dirty = true;
}

void Craft::Text::SetWrapLength(uint32_t wrapLength) noexcept
{
    _wrapLength = wrapLength;
    _dirty = true;
}

void Craft::Text::SetText(std::string text)
{
    _text = std::move(text);
    _dirty = true;
}

void Craft::Text::SetFontSize(uint16_t size) noexcept
{
    _font.SetSize(size);
    _dirty = true;
}

std::string Craft::Text::GetText() const
{
    return _text;
}

Craft::Color Craft::Text::GetFontColor() const noexcept
{
    return _color;
}

size_t Craft::Text::InsertText(const std::string &s, size_t pos)
{
    _text.insert(pos, s);
    _dirty = true;
    return s.size();
}

size_t Craft::Text::InsertTextBack(const std::string &s)
{
    _text.insert(_text.size() - 1, s);
    _dirty = true;
    return s.size();
}

bool Craft::Text::IsEmpty() const noexcept
{
    return _text.empty();
}

void Craft::Text::ClearText()
{
    _text.clear();
    _dirty = true;
}

// size is point to last char + 1
size_t Craft::Text::EraseFrontWord(size_t wordEndPosition)
{
    if (wordEndPosition == 0)
    {
        return 0;
    }
    auto [wordStartIndex, wordSize] = _FindFrontWordStartIndex(wordEndPosition - 1, _text);
    _text.erase(wordStartIndex, wordSize);
    _dirty = true;
    return wordSize;
}

size_t Craft::Text::PopBackLine()
{
    size_t lineSize = 0;
    auto index = _text.find_last_of('\n');
    if (index != std::string::npos)
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

bool Craft::Text::_IsSpacer(char c) const noexcept
{
    return c == ' ' || c == '\n' || c == '\t';
}

size_t Craft::Text::GetTextSize() const noexcept
{
    return _text.size();
}

// TODO: api design problem, length and pos
std::tuple<size_t, size_t> Craft::Text::GetTextSpace(size_t length, size_t pos) const
{
    return _font.GetTextSpace(_text.substr(pos, length));
}

std::tuple<size_t, size_t> Craft::Text::GetUTF8TextSpace(size_t length, size_t pos) const
{
    return _font.GetUTF8TextSpace(_text.substr(pos, length));
}

void Craft::Text::EraseStr(size_t pos, size_t size)
{
    _text.erase(pos, size);
    _dirty = true;
}

// base index is point to last char
// not point to last char + 1
std::tuple<size_t, size_t> Craft::Text::_FindFrontWordStartIndex(size_t baseIndex, const std::string& text) const
{
    // TODO:baseIndex > text.size()
    // 字符串操作都是类似问题
    size_t wordSize = 0;
    int wordStartIndex = baseIndex, lastCharIndex = baseIndex;
    for(;lastCharIndex >= 0; --lastCharIndex)
    {
        if (text[lastCharIndex] != ' ')
        {
            wordStartIndex = lastCharIndex - 1;
            for(;wordStartIndex >= 0; --wordStartIndex)
            {
                if (_IsSpacer(text[wordStartIndex]))
                {
                    wordSize = baseIndex + 1 - wordStartIndex;
                    break;
                }
            }
            if (wordStartIndex == -1)
            {
                wordSize = baseIndex + 1;
                wordStartIndex = 0;
            }
            break;
        }
    }
    if (lastCharIndex == -1)
    {
        wordSize = baseIndex + 1;
        wordStartIndex = 0;
    }
    return std::make_tuple(wordStartIndex, wordSize);
}

size_t Craft::Text::_AdjustShowTextureWidth(const Renderer& renderer, int textEndPosition)
{
    size_t space = 0;
    if (_showTextBeginIndex == textEndPosition && _showTextBeginIndex != 0)
    {
        --_showTextBeginIndex;
    }
    for(auto textBeginIndex = _showTextBeginIndex; textBeginIndex < textEndPosition; ++textBeginIndex)
    {
        space = std::get<0>(_font.GetTextSpace(_text.substr(textBeginIndex, textEndPosition - textBeginIndex)));
        if (space <= _wrapLength)
        {
            _ResetTexture(renderer, textBeginIndex);
            _showTextBeginIndex = textBeginIndex;
            break;
        }
    }
    // TODO:queryTexture
    return space;
}

int Craft::Text::GetTextIndexFromOffsetX(int offsetX) const
{
    for(auto subStrSize = 1; subStrSize <= _text.size(); ++subStrSize)
    {
        auto [w, h] = GetTextSpace(subStrSize, _showTextBeginIndex);
        if (offsetX < w)
        {
            return static_cast<int>(_showTextBeginIndex) + subStrSize - 1;
        }
    }
    // TODO:计算如果单击空位置的处理，考虑到部分渲染的问题
    return -1;
}
//TODO: 文字渲染长度
std::string Craft::Text::GetSubStr(size_t pos, size_t size) const
{
    return _text.substr(pos, size);
}

size_t Craft::Text::GetTextShowHeight() const
{
    return std::get<1>(GetTextSpace(_text.size()));
}

size_t Craft::Text::GetFullTextShowWidth() const
{
    return std::get<0>(GetTextSpace(_text.size()));
}

size_t Craft::Text::GetShowTextBeginIndex()
{
    return _showTextBeginIndex;
}

size_t Craft::Text::GetTextShowWidth(size_t pos, size_t length) const
{
    return std::get<0>(GetTextSpace(length, pos));
}

size_t Craft::Text::GetShowTextWidth(size_t length) const
{
    return std::get<0>(GetTextSpace(length, _showTextBeginIndex));
}

void Craft::Text::SetAutoBreakLine(bool isAutoBreakLine) noexcept
{
    _autoBreakLine = isAutoBreakLine;
}
