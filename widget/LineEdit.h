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
    struct Cursor
    {
    public:
        Cursor():_cursor(0){}

        size_t Increase(int span = 1, size_t maxSize = 0) noexcept
        {
            // TODO:负数间隔
            if(maxSize == 0 || ((_cursor + span) <= maxSize))
            {
                _cursor += span;
            }
            else
            {
                _cursor = maxSize;
            }
            std::cout << "_cursor + " << span << " is" << _cursor << std::endl;
            return _cursor;
        }

        size_t Decrease(int span = 1) noexcept
        {
            //if((_cursor - span) >= 0)
            if(_cursor >= span)
            {
                _cursor -= span;
            }
            else
            {
                _cursor = 0;
            }
            std::cout << "_cursor - " << span << " is" << _cursor << std::endl;;
            return _cursor;
        }

        void Reset() noexcept
        {
            std::cout << "cursor reset 0" << std::endl;
            _cursor = 0;
        }

        operator size_t() const
        {
            return _cursor;
        }

    private:
        size_t _cursor;
    };

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

        // direct position which will write char
        // it has same value as str.size()
        Cursor _cursor;
    };
}


#endif //GWUI_LINEEDIT_H
