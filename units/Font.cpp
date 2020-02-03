//
// Created by fusionbolt on 2020-01-24.
//

#include "Font.h"

GWUI::Font::Font(u_int16_t size, const std::string &path):
    _path(path), _size(size), _font(TTF_OpenFont(path.c_str(), size), TTF_CloseFont)
{
    if(_font == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

TTF_Font *GWUI::Font::GetFontPtr() noexcept
{
    return _font.get();
}

void GWUI::Font::SetSize(uint16_t size) noexcept
{
    _font.reset(TTF_OpenFont(_path.c_str(), size), TTF_CloseFont);
    _size = size;
}
