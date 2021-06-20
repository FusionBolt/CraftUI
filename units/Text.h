//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_TEXT_H
#define GWUI_TEXT_H

#include <string>
#include <SDL.h>

#include "Font.h"
#include "Renderer.h"

namespace Craft
{
    class Text
    {
    public:
        explicit Text(std::string text = "", uint16_t size = 15, const Color &color = Craft::Black, uint32_t wrapLength = 200);

        int Draw(Renderer& renderer, int textEndPosition = -1);

        void SetPosition(Point position) noexcept;

        void SetColor(Color color) noexcept;

        void SetWrapLength(uint32_t wrapLength) noexcept;

        void SetText(std::string text);

        void SetAutoBreakLine(bool isAutoBreakLine) noexcept;

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

        void EraseStr(size_t pos, size_t size);

        void SetFontSize(uint16_t size) noexcept;

        [[nodiscard]] bool IsEmpty() const noexcept;

        [[nodiscard]] size_t GetTextShowHeight() const;

        [[nodiscard]] size_t GetFullTextShowWidth() const;

        // TODO:能否分离出一个解析渲染空间以及计算坐标的类？？
        // TODO:api 参数顺序问题
        [[nodiscard]] std::tuple<size_t, size_t> GetTextSpace(size_t length, size_t pos = 0) const;

        [[nodiscard]] size_t GetTextShowWidth(size_t pos, size_t length) const;

        [[nodiscard]] size_t GetShowTextWidth(size_t length) const;

        [[nodiscard]] std::tuple<size_t, size_t> GetUTF8TextSpace(size_t length, size_t pos = 0) const;

        [[nodiscard]] int GetTextIndexFromOffsetX(int offsetX) const;

        [[nodiscard]] std::string GetSubStr(size_t pos, size_t size) const;

        size_t GetShowTextBeginIndex();

    private:
        void _ResetTexture(const Renderer& renderer, size_t offset = 0);

        size_t _AdjustShowTextureWidth(const Renderer& renderer, int textEndPosition);

        [[nodiscard]] bool _IsSpacer(char c) const noexcept;

        [[nodiscard]] std::tuple<size_t, size_t> _FindFrontWordStartIndex(size_t baseIndex, const std::string& text) const;

        Point _position;

        Color _color;

        uint16_t _fontSize;

        std::string _text;

        Font _font;

        uint32_t _wrapLength;

        std::shared_ptr<SDL_Texture> _texture;

        bool _dirty;

        bool _autoBreakLine;

        size_t _showTextBeginIndex;
    };
}



#endif //GWUI_TEXT_H
