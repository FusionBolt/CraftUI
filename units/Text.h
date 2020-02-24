//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_TEXT_H
#define GWUI_TEXT_H

#include <string>

#include "SDL.h"
#include "Font.h"
#include "Renderer.h"

namespace GWUI
{
    class Text
    {
    public:
        explicit Text(std::string text = "", uint16_t size = 15, const Color &color = GWUI::Black, uint32_t wrapLength = 200);

        int Draw(Renderer& renderer, int textEndPosition = -1);

        void SetPosition(Point position) noexcept;

        void SetColor(Color color) noexcept;

        void SetWrapLength(uint32_t wrapLength) noexcept;

        void SetText(std::string text);

        void ClearText();

        void PopBackChar();

        void InsertChar(char c);

        size_t InsertText(const std::string &s, size_t pos);

        size_t InsertTextBack(const std::string &s);

        size_t EraseFrontWord(size_t wordEndPosition);

        size_t PopBackLine();

        std::string GetText() const noexcept;

        size_t GetTextSize() const noexcept;

        Color GetFontColor() const noexcept;

        void SetFontSize(uint16_t size) noexcept;

        bool IsEmpty() const noexcept;

        std::tuple<size_t, size_t> GetTextSpace(size_t length) const;

        std::tuple<size_t, size_t> GetUTF8TextSpace(size_t length) const;

        void EraseStr(size_t pos, size_t length);

    private:
        void _ResetTexture(Renderer& renderer);

        size_t _AdjustTextureArea(const Renderer& renderer, int textEndPosition);

        bool _IsSpacer(char c) const noexcept;

        std::tuple<size_t, size_t> _FindFrontWordStartIndex(size_t baseIndex, const std::string& text);

        Point _position;

        Color _color;

        uint16_t _fontSize;

        std::string _text;

        Font _font;

        uint32_t _wrapLength;

        std::shared_ptr<SDL_Texture> _texture;

        bool _dirty = false;
    };
}



#endif //GWUI_TEXT_H
