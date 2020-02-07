//
// Created by fusionbolt on 2020-02-03.
//

#include "ButtonGroup.h"

void GWUI::ButtonGroup::AddButton(std::shared_ptr<AbstractButton> button)
{
    _buttons.push_back(button);
    button->_SetButtonGroup(shared_from_this());
    std::cout << "add button" << std::endl;
}

bool GWUI::ButtonGroup::IsExclusive() const noexcept
{
    return _exclusive;
}

void GWUI::ButtonGroup::RemoveButton(std::shared_ptr<AbstractButton> button)
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

std::shared_ptr<GWUI::AbstractButton> GWUI::ButtonGroup::GetCheckedButton() noexcept
{
    return _checkedButton.lock();
}

void GWUI::ButtonGroup::SetCheckedButton(std::shared_ptr<AbstractButton> button) noexcept
{
    _checkedButton = button;
}
