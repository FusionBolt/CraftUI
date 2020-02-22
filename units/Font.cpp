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

void GWUI::Font::SetSize(uint16_t size) noexcept
{
    _font.reset(TTF_OpenFont(_path.c_str(), size), TTF_CloseFont);
    _size = size;
}

std::shared_ptr<SDL_Surface>
GWUI::Font::RenderTextBlendedWrapped(const std::string &text, GWUI::Color color, int wrapLength)
{
    return std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Blended_Wrapped(
                    _font.get(),
                    text.c_str(),
                    color,
                    wrapLength
            ), SDL_FreeSurface);
}
