//
// Created by fusionbolt on 2020-01-24.
//

#include "Text.h"

GWUI::Text::Text(std::string text, uint16_t size, const GWUI::Color &color, uint32_t wrapLength):
    _text(std::move(text)), _color(color), _size(size), _font(size),
    _wrapLength(wrapLength)
{
    //_ResetTexture();
    _position = Point{20, 20};
}

void GWUI::Text::Draw(Renderer& renderer)
{
    if (_dirty)
    {
        _ResetTexture(renderer);
        _dirty = false;
    }
    renderer.RenderTexture(_texture, _position);
}

void GWUI::Text::_ResetTexture(Renderer& renderer)
{
    auto ttf = _font.RenderTextBlendedWrapped(_text, _color, _wrapLength);
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

void GWUI::Text::AppendChar(char c)
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

void GWUI::Text::AppendStr(const std::string& s1)
{
    _text.append(s1);
    _dirty = true;
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

void GWUI::Text::PopBackWord()
{
    for(auto lastCharIndex = static_cast<int>(_text.size()) - 1; lastCharIndex >= 0; --lastCharIndex)
    {
        if(_text[lastCharIndex] != ' ')
        {
            auto spaceIndex = lastCharIndex - 1;
            while(spaceIndex >= 0)
            {
                if(_IsSpacer(_text[spaceIndex]))
                {
                    _text.erase(spaceIndex, _text.size() - spaceIndex);
                    break;
                }
                spaceIndex--;
            }
            if(spaceIndex == -1)
            {
                _text.clear();
            }
            break;
        }
    }
    _dirty = true;
}

void GWUI::Text::PopBackLine()
{
    auto index = _text.find_last_of('\n');
    if(index != std::string::npos)
    {
        _text.erase(index, _text.size() - index);
    }
    else
    {
        _text.clear();
    }
    _dirty = true;
}

bool GWUI::Text::_IsSpacer(char c)
{
    return c == ' ' || c == '\n' || c == '\t';
}
