//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_TEXT_H
#define GWUI_TEXT_H

#include <string>
#include <SDL.h>

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

        [[nodiscard]] std::string GetText() const;

        [[nodiscard]] size_t GetTextSize() const noexcept;

        [[nodiscard]] Color GetFontColor() const noexcept;

        void SetFontSize(uint16_t size) noexcept;

        [[nodiscard]] bool IsEmpty() const noexcept;

        [[nodiscard]] size_t GetTextHeight() const;

        [[nodiscard]] size_t GetTextWidth() const;

        [[nodiscard]] std::tuple<size_t, size_t> GetTextSpace(size_t length, size_t pos = 0) const;

        [[nodiscard]] std::tuple<size_t, size_t> GetUTF8TextSpace(size_t length, size_t pos = 0) const;

        void EraseStr(size_t pos, size_t size);

        [[nodiscard]] int GetTargetCharIndex(int offsetX) const;

        [[nodiscard]] std::string GetSubStr(size_t pos, size_t size) const;

    private:
        void _ResetTexture(Renderer& renderer);

        size_t _AdjustTextureArea(const Renderer& renderer, int textEndPosition);

        [[nodiscard]] bool _IsSpacer(char c) const noexcept;

        [[nodiscard]] std::tuple<size_t, size_t> _FindFrontWordStartIndex(size_t baseIndex, const std::string& text) const;

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
