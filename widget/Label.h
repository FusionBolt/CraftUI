//
// Created by fusionbolt on 2020-01-28.
//

#ifndef GWUI_LABEL_H
#define GWUI_LABEL_H

#include <variant>
#include "Widget.h"
#include "../units/Text.h"
#include "../units/Image.h"

namespace GWUI
{
    class Label : public Widget
    {
    public:
        explicit Label(std::string text = "");

        explicit Label(Image img);

        void Draw(Renderer &renderer) override;

        void SetFontSize(uint16_t size);

        void SetPosition(Point position);

        void SetFontColor(Color color);

        void SetText(const std::string& text);

        void SetPicture(Image img);

        void SetGeometry(Rect rect) noexcept override;

    private:
        Text _text;

        Image _img;

        bool _isImg = false;
    };
}



#endif //GWUI_LABEL_H
