//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_FONT_H
#define GWUI_FONT_H

#include <string>

#include "SDL_ttf.h"
#include "Renderer.h"

namespace GWUI
{
    constexpr auto FONT_STYLE_NORMAL = 0x00;
    constexpr auto FONT_STYLE_BOLD = 0x01;
    constexpr auto FONT_STYLE_ITALIC	= 0x02;
    constexpr auto FONT_STYLE_UNDERLINE = 0x04;
    constexpr auto FONT_STYLE_STRIKETHROUGH = 0x08;

    class Font
    {
    public:
        explicit Font(u_int16_t size = 25, const std::string& path = "/Users/fusionbolt/CLionProjects/GWUI/source/PingFang.ttf");

        std::shared_ptr<SDL_Surface> RenderTextBlendedWrapped(const std::string& text, Color color, int wrapLength, int textOffset = 0);

        std::shared_ptr<SDL_Surface> RenderTextBlended(const std::string& text, Color color);

        void SetSize(uint16_t size) noexcept;

        [[nodiscard]] std::tuple<size_t, size_t> GetTextSpace(const std::string& text) const;

        [[nodiscard]] std::tuple<size_t, size_t> GetUTF8TextSpace(const std::string& text) const;

        void SetFont(const std::string& path);

    private:
        void _ResetFont();

        std::shared_ptr<TTF_Font> _font;

        std::string _path;

        u_int16_t _size;

        int _style = FONT_STYLE_NORMAL;
    };
}



#endif //GWUI_FONT_H
