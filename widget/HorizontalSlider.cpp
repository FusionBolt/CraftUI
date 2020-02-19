//
// Created by fusionbolt on 2020-01-29.
//

#include "HorizontalSlider.h"

GWUI::HorizontalSlider::HorizontalSlider() : Widget()
{

}

void GWUI::HorizontalSlider::Draw(GWUI::Renderer renderer)
{
    Widget::Draw(renderer);
    auto x = _geometry.x;
    _chooseRect.Draw(renderer);
    // all
    renderer.RendererLine(Point{x, _geometry.y + 10},
            Point{x + _lineWidth, _geometry.y + 10}, {0, 0, 0});
    // choose
    if(_chooseRect.GetRect().x > x)
    {
        renderer.RendererLine(Point{x, _geometry.y + 10},
        Point{_chooseRect.GetRect().x, _geometry.y + 10}, {50, 205, 50});
    }

}

void GWUI::HorizontalSlider::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry({rect.x, rect.y, rect.w, rect.h});
    _chooseRect.SetRect({_geometry.x - _chooseRectWidth / 2, _geometry.y, _chooseRectWidth, _chooseRectWidth});
}

void GWUI::HorizontalSlider::SetValue(int value)
{
    _value = value;
    _chooseRect.SetRect({_geometry.x + static_cast<int>(static_cast<double>(_value - _minSize) / (_maxSize-_minSize) * _lineWidth) - _chooseRectWidth / 2,
                         _geometry.y, _chooseRectWidth, _chooseRectWidth});
}

void GWUI::HorizontalSlider::SetValueRange(int minSize, int maxSize) noexcept
{
    assert(minSize != maxSize);
    _maxSize = maxSize;
    _minSize = minSize;
}

void GWUI::HorizontalSlider::MousePressEvent(const MouseEvent &mouseEvent)
{
    Widget::MousePressEvent(mouseEvent);
    _isChoose = true;
    std::cout << "On Click Slider" << std::endl;
}

void GWUI::HorizontalSlider::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    Widget::MouseReleaseEvent(mouseEvent);
    _isChoose = false;
}

void GWUI::HorizontalSlider::MouseMotionEvent(const MouseEvent &mouseEvent)
{
    Widget::MouseMotionEvent(mouseEvent);
    auto mousePosition = mouseEvent.GetPosition();
    if(_isChoose)
    {
        std::cout << "On Mouse Motion" << std::endl;
        if(mousePosition.x > _geometry.x)
        {
            if(mousePosition.x < _geometry.x + _lineWidth)
            {
                _value = static_cast<int>(static_cast<double>(mousePosition.x - _geometry.x) / _lineWidth * (_maxSize - _minSize)) + _minSize;
                std::cout << mousePosition.x << " " << _geometry.x << " " << static_cast<double>(mousePosition.x - _geometry.x) / _maxSize << std::endl;
            }
            else
            {
                _value = _maxSize;
            }
        }
        else
        {
            _value = _minSize;
        }
        std::cout << _value << std::endl;
        SetValue(_value);
    }
}
