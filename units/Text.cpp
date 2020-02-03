//
// Created by fusionbolt on 2020-01-24.
//

#include "Text.h"

GWUI::Text::Text(std::string text, uint16_t size, const GWUI::Color &color, uint32_t wrapLength):
    _text(std::move(text)), _color(color), _size(size), _font(size), _wrapLength(wrapLength)
{
    //_ResetTexture();
    _position = Point{20, 20};
}

void GWUI::Text::Draw(Renderer renderer)
{
    _ResetTexture(renderer);
    RenderTexture(_texture, renderer.GetRenderer(), _position);
}

void GWUI::Text::SetPosition(Point position) noexcept
{
    _position = position;
}

void GWUI::Text::PopBackChar()
{
    if(!_text.empty())
    {
        _text.pop_back();
    }
   // _ResetTexture();
}

void GWUI::Text::AppendChar(char c)
{
    _text.append({c});
    //_ResetTexture();
    std::cout << _text << std::endl;
}

void GWUI::Text::_ResetTexture(Renderer renderer)
{
    auto ttf = TTF_RenderText_Blended_Wrapped(_font.GetFontPtr(), _text.c_str(), _color, _wrapLength);
    _texture.reset(
            SDL_CreateTextureFromSurface(renderer.GetRenderer().get(),
                                         ttf),
            SDL_DestroyTexture
    );
    SDL_FreeSurface(ttf);
}

void GWUI::Text::SetColor(GWUI::Color color) noexcept
{
    _color = color;
    //_ResetTexture();
}

void GWUI::Text::SetWrapLength(uint32_t wrapLength) noexcept
{
    _wrapLength = wrapLength;
    //_ResetTexture();
}

void GWUI::Text::SetText(std::string text)
{
    _text = std::move(text);
    //_ResetTexture();
}

std::string GWUI::Text::GetText() const noexcept
{
    return _text;
}

GWUI::Color GWUI::Text::GetColor() const noexcept
{
    return _color;
}

void GWUI::Text::SetFontSize(uint16_t size) noexcept
{
    _font.SetSize(size);
}
