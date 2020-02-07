//
// Created by fusionbolt on 2020-01-24.
//

#include "Button.h"
#include "ButtonGroup.h"

GWUI::Button::Button(const std::string &text):
    AbstractButton(text)
{
}

void GWUI::Button::Draw(Renderer renderer)
{
    RendererRectangle(renderer.GetRenderer(), GetGeometry(), {255, 255, 255});
    _text.Draw(renderer);
    Widget::Draw(renderer);
}

void GWUI::Button::SetGeometry(GWUI::Rect rect) noexcept
{
    _rect = rect;
    _text.SetPosition({rect.x + 10, rect.y + 10});
    Widget::SetGeometry(rect);
}

void GWUI::Button::MousePressEvent(const MouseEvent &mouseEvent)
{
    if(JudgeCoincide(mouseEvent.GetPosition(), GetGeometry()))
    {
        auto buttonGroup = _buttonGroup;
        if(buttonGroup == nullptr)
        {
            _checked = !_checked;
        }
        else if(_checked)
        {
            buttonGroup->SetCheckedButton(nullptr);
            _checked = false;
        }
        else
        {
            auto thisPtr = std::dynamic_pointer_cast<AbstractButton>(shared_from_this());
            if(!buttonGroup->IsExclusive() ||
               (buttonGroup->IsExclusive() &&
                buttonGroup->GetCheckedButton() == nullptr))
            {
                _checked = true;
                buttonGroup->SetCheckedButton(thisPtr);
            }
        }
        if(_onClicked != nullptr)
        {
            std::invoke(_onClicked, _checked);
        }
    }
    Widget::MousePressEvent(mouseEvent);
}

void GWUI::Button::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    Widget::MouseReleaseEvent(mouseEvent);
}