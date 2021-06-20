//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_LINEEDIT_H
#define GWUI_LINEEDIT_H

#include "Widget.h"
#include "../units/Rectangle.h"
#include "../units/Text.h"
#include "../units/Cursor.h"
#include "../units/SelectArea.h"

namespace Craft
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

        void MouseReleaseEvent(const MouseEvent &mouseEvent) override;

        void MouseMotionEvent(const MouseEvent &mouseEvent) override;

    private:
        void _SetCursor(int mouseX);

        Rectangle _rect;

        Text _text;

        bool _editing;

        // direct position which will write char
        // it has same value as str.size()
        Cursor _cursor;

        Rect _select;

        Point _firstClickPosition;

        SelectArea _selectArea;
    };
}


#endif //GWUI_LINEEDIT_H
