//
// Created by fusionbolt on 2020-01-30.
//

#include "CheckBox.h"
#include "ButtonGroup.h"

Craft::CheckBox::CheckBox(const std::string& text) :
    AbstractButton(text)
{

}

void Craft::CheckBox::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    renderer.RenderFillRectangle(_checkedRectangle, Craft::White);
    renderer.RenderRectangle(_checkedRectangle, Craft::Black);

    _text.Draw(renderer);

    if (_checked)
    {
        auto smallRectWidth = 10;
        auto& rect = _checkedRectangle;
        renderer.RenderFillRectangle(
                {rect.x + smallRectWidth / 2, rect.y + smallRectWidth / 2,
                 rect.w - smallRectWidth, rect.h - smallRectWidth},
                Craft::Black);
    }
}

void Craft::CheckBox::SetGeometry(Craft::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    int rectWidth = 20;
    auto widgetY = rect.y + rect.h / 2 - rectWidth / 2;
    _checkedRectangle = {rect.x, widgetY, rectWidth, rectWidth};
    _text.SetPosition({rect.x + rectWidth + 2, widgetY});
    // 2 used space
}


