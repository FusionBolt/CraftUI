//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_LINEEDIT_H
#define GWUI_LINEEDIT_H

#include "Widget.h"
#include "../units/Rectangle.hpp"
#include "../units/Text.h"

namespace GWUI
{
    class LineEdit : public Widget
    {
    public:
        explicit LineEdit();

        void Draw(Renderer &renderer) override;

        void SetGeometry(Rect rect) noexcept override;

    protected:
        void KeyReleaseEvent(const KeyBoardEvent &keyBoardEvent) override;

        void MousePressEvent(const MouseEvent &mouseEvent) override;

        void KeyPressEvent(const KeyBoardEvent &keyBoardEvent) override;

    private:
        Rectangle _rect;

        Text _text;

        bool _editing;
    };
}


#endif //GWUI_LINEEDIT_H
