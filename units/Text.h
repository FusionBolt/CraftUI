//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_TEXT_H
#define GWUI_TEXT_H

#include <string>

#include "SDL.h"
#include "Font.h"
#include "../utils/Util.hpp"

namespace GWUI
{

    class Text
    {
    public:
        explicit Text(std::string text = "", uint16_t size = 15, const Color &color = {0, 0, 0}, uint32_t wrapLength = 200);

        void Draw(Renderer renderer);

        void SetPosition(Point position) noexcept;

        void SetColor(Color color) noexcept;

        void SetWrapLength(uint32_t wrapLength) noexcept;

        void SetText(std::string text);

        void PopBackChar();

        void AppendChar(char c);

        std::string GetText() const noexcept;

        Color GetColor() const noexcept;

        void SetFontSize(uint16_t size) noexcept;

    private:
        void _ResetTexture(Renderer renderer);

        Point _position;

        Color _color;

        uint16_t _size;

        std::string _text;

        Font _font;

        uint32_t _wrapLength;

        std::shared_ptr<SDL_Texture> _texture;
    };
}



#endif //GWUI_TEXT_H