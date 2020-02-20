//
// Created by fusionbolt on 2020-01-25.
//

#ifndef GWUI_TEXTAREA_H
#define GWUI_TEXTAREA_H

#include "../units/Rectangle.hpp"
#include "../units/Text.h"
#include "Widget.h"

namespace GWUI
{
    class TextArea : public Widget
    {
    public:
        explicit TextArea(Rect rect = {});

        void Draw(Renderer &renderer) override;

        void SetGeometry(Rect rect) noexcept override;

        void SetText(std::string text);

    protected:
        void KeyPressEvent(const KeyBoardEvent &keyBoardEvent) override;

        void MousePressEvent(const MouseEvent &mouseEvent) override;

    private:
        Rectangle _rectangle;

        Text _text;

        bool _editing = false;
    };
}



#endif //GWUI_TEXTAREA_H
