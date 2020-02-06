//
// Created by fusionbolt on 2020-02-03.
//

#ifndef GWUI_BUTTONGROUP_H
#define GWUI_BUTTONGROUP_H

#include "AbstractButton.h"

namespace GWUI
{
    class ButtonGroup : public std::enable_shared_from_this<ButtonGroup>
    {
    public:
        ButtonGroup() = default;

        void AddButton(std::shared_ptr<AbstractButton> button);

        void RemoveButton(std::shared_ptr<AbstractButton> button);

        std::shared_ptr<AbstractButton> GetCheckedButton() noexcept;

        void SetCheckedButton(std::shared_ptr<AbstractButton> button) noexcept;

        bool IsExclusive() const noexcept;

    private:
        bool _exclusive = true;

        std::shared_ptr<AbstractButton> _checkedButton;

        std::vector<std::shared_ptr<AbstractButton>> _buttons;
    };
}

#endif //GWUI_BUTTONGROUP_H
