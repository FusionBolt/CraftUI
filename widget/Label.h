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
        explicit Label(const std::string& text = "");

        void Draw(Renderer renderer) override;

        void SetFontSize(uint16_t size);

        void SetPosition(Point position);

        void SetFontColor(Color color);

        void SetText(const std::string& text);

        void SetPicture(const std::string& path, Rect rect);

    private:
        Text _text;

        Image _img;

        bool _isImg = false;
    };
}



#endif //GWUI_LABEL_H
