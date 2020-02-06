//
// Created by fusionbolt on 2020-01-30.
//

#include "CheckBox.h"
#include "ButtonGroup.h"

GWUI::CheckBox::CheckBox(const std::string& text) :
    AbstractButton(text)
{
    _text.SetColor({255, 255, 255});
}

void GWUI::CheckBox::Draw(GWUI::Renderer renderer)
{
    _checkRectangle.Draw(renderer);
    _text.Draw(renderer);
    if(_checked)
    {
        auto smallRectWidth = 10;
        auto rect = _checkRectangle.GetRect();
        RendererRectangle(renderer.GetRenderer(),
                {rect.x + smallRectWidth / 2, rect.y + smallRectWidth / 2,
                 rect.w - smallRectWidth, rect.h - smallRectWidth},
                {0,0,0});
    }
    Widget::Draw(renderer);
}

void GWUI::CheckBox::MousePressEvent(const MouseEvent &mouseEvent)
{
    if(JudgeCoincide(mouseEvent.GetPosition(), _checkRectangle.GetRect()))
    {
        auto buttonGroup = _buttonGroup.lock();
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

void GWUI::CheckBox::SetGeometry(GWUI::Rect rect) noexcept
{
    int rectWidth = 20;
    auto widgetY = rect.y + rect.h / 2 - rectWidth / 2;
    _checkRectangle.SetRect({rect.x, widgetY, rectWidth, rectWidth});
    _text.SetPosition({rect.x + rectWidth + 2, widgetY});
    // 2 used space
    Widget::SetGeometry(rect);
}


