//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_HORIZONTALSLIDER_H
#define GWUI_HORIZONTALSLIDER_H

#include "Widget.h"
#include "../units/Rectangle.h"

namespace GWUI
{
    class HorizontalSlider : public Widget
    {
    public:
        HorizontalSlider();

        void Draw(Renderer &renderer) override;

        void SetGeometry(Rect rect) noexcept override;

        void SetValue(int value);

        void SetValueRange(int minSize, int maxSize) noexcept;

    protected:
        void MousePressEvent(const MouseEvent &mouseEvent) override;

        void MouseReleaseEvent(const MouseEvent &mouseEvent) override;

        void MouseMotionEvent(const MouseEvent &mouseEvent) override;

    private:
        int _maxSize = 100, _minSize = -100;

        size_t _sizeIncrement = 1;

        Rectangle _chooseRect;

        int _chooseRectWidth = 20;

        int _value = _minSize;

        bool _isChoose = false;

        int _lineWidth = 150;
    };
}



#endif //GWUI_HORIZONTALSLIDER_H
