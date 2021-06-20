//
// Created by fusionbolt on 2020-02-03.
//

#include "ButtonGroup.h"

void Craft::ButtonGroup::AddButton(std::shared_ptr<AbstractButton> button)
{
    _buttons.push_back(button);
    button->_SetButtonGroup(std::dynamic_pointer_cast<ButtonGroup>(shared_from_this()));
    std::cout << "add button" << std::endl;
}

bool Craft::ButtonGroup::IsExclusive() const noexcept
{
    return _exclusive;
}

void Craft::ButtonGroup::RemoveButton(std::shared_ptr<AbstractButton> button)
{
    for(auto iter = _buttons.begin(); iter != _buttons.end(); ++iter)
    {
        if(iter->lock() == button)
        {
            std::cout << "remove button" << std::endl;
            button->_SetButtonGroup(nullptr);
            _buttons.erase(iter);
            break;
        }
    }
}

std::shared_ptr<Craft::AbstractButton> Craft::ButtonGroup::GetCheckedButton() noexcept
{
    return _checkedButton.lock();
}

void Craft::ButtonGroup::SetCheckedButton(std::shared_ptr<AbstractButton> button) noexcept
{
    _checkedButton = button;
}
