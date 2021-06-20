//
// Created by fusionbolt on 2020-01-30.
//

#include "AbstractButton.h"
#include "ButtonGroup.h"

#include <utility>

Craft::AbstractButton::AbstractButton(const std::string& text) :
    Widget(),_text(text)
{

}

bool Craft::AbstractButton::IsChecked() const noexcept
{
    return _checked;
}

std::string Craft::AbstractButton::GetText() const
{
    return _text.GetText();
}

void Craft::AbstractButton::SetText(const std::string &text)
{
    _text.SetText(text);
}

bool Craft::AbstractButton::IsCheckable() const noexcept
{
    return _checkable;
}

void Craft::AbstractButton::_SetButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup)
{
    _buttonGroup = buttonGroup;
}

void Craft::AbstractButton::OnClicked(std::function<void(bool)> f)
{
    _onClicked = std::move(f);
}

bool Craft::AbstractButton::IsExclusive() const noexcept
{
    return _exclusive;
}

void Craft::AbstractButton::SetExclusive(bool isExclusive) noexcept
{
    _exclusive = isExclusive;
}

void Craft::AbstractButton::MousePressEvent(const Craft::MouseEvent &mouseEvent)
{
    if (JudgeCoincide(mouseEvent.GetPosition(), _checkedRectangle))
    {
        auto buttonGroup = _buttonGroup;
        if (buttonGroup == nullptr)
        {
            _checked = !_checked;
        }
        else if (_checked)
        {
            buttonGroup->SetCheckedButton(nullptr);
            _checked = false;
        }
        else
        {
            auto thisPtr = std::dynamic_pointer_cast<AbstractButton>(shared_from_this());
            if (!buttonGroup->IsExclusive() ||
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
