//
// Created by fusionbolt on 2020-01-30.
//

#ifndef GWUI_ABSTRACTBUTTON_H
#define GWUI_ABSTRACTBUTTON_H


#include "Widget.h"
#include "../units/Text.h"

namespace GWUI
{
    class ButtonGroup;

    class AbstractButton : public Widget
    {
    public:
        explicit AbstractButton(const std::string& text = "button");

        bool IsChecked() const noexcept;

        // TODO:check or down??
        bool IsCheckable() const noexcept;

        std::string GetText() const;

        void SetText(const std::string& text);

        void OnClick(std::function<void(bool)> f);
        // TODO:need virtual event?
    protected:
        friend class ButtonGroup;

        void _SetButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup);
        // TODO:直接调用这个来管理group会有问题
        bool _checked = false;

        bool _checkable = true;

        Text _text;

        std::function<void(bool)> _onClicked;

        std::weak_ptr<ButtonGroup> _buttonGroup;
    };
}


#endif //GWUI_ABSTRACTBUTTON_H
