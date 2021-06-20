//
// Created by fusionbolt on 2020-01-24.
//

#include "Font.h"

Craft::Font::Font(u_int16_t size, const std::string &path):
    _path(path), _size(size), _font(TTF_OpenFont(path.c_str(), size), TTF_CloseFont)
{
    if(_font == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

void Craft::Font::SetSize(uint16_t size) noexcept
{
    _size = size;
    _ResetFont();
}

std::shared_ptr<SDL_Surface>
Craft::Font::RenderTextBlendedWrapped(const std::string &text, Craft::Color color, int wrapLength, int textOffset)
{
    return std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Blended_Wrapped(
                    _font.get(),
                    text.c_str() + textOffset,
                    color,
                    wrapLength
            ), SDL_FreeSurface);
}

std::shared_ptr<SDL_Surface> Craft::Font::RenderTextBlended(const std::string &text, Craft::Color color)
{
    return std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Blended(
                    _font.get(),
                    text.c_str(),
                    color
            ), SDL_FreeSurface);
}

std::tuple<size_t, size_t> Craft::Font::GetTextSpace(const std::string& text) const
{
    int w, h;
    TTF_SizeText(_font.get(), text.c_str(), &w, &h);
    return std::make_tuple(w, h);
}

std::tuple<size_t, size_t> Craft::Font::GetUTF8TextSpace(const std::string &text) const
{
    int w, h;
    TTF_SizeUTF8(_font.get(), text.c_str(), &w, &h);
    return std::make_tuple(w, h);
}

void Craft::Font::SetFont(const std::string& path)
{
    _path = path;
    _ResetFont();
}

void Craft::Font::_ResetFont()
{
    _font.reset(TTF_OpenFont(_path.c_str(), _size), TTF_CloseFont);
}