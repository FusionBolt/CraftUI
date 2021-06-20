//
// Created by fusionbolt on 2020-01-30.
//

#ifndef GWUI_ABSTRACTBUTTON_H
#define GWUI_ABSTRACTBUTTON_H


#include "Widget.h"
#include "../units/Text.h"

namespace Craft
{
    class ButtonGroup;

    class AbstractButton : public Widget
    {
    public:
        explicit AbstractButton(const std::string& text = "button");

        bool IsChecked() const noexcept;

        bool IsCheckable() const noexcept;

        std::string GetText() const;

        void SetText(const std::string& text);

        void OnClicked(std::function<void(bool)> f);

        bool IsExclusive() const noexcept;

        void SetExclusive(bool isExclusive) noexcept;

    protected:
        friend class ButtonGroup;

        ~AbstractButton() override = default;

        void MousePressEvent(const MouseEvent &mouseEvent) override;

        void _SetButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup);

        bool _checked = false;

        bool _checkable = true;

        bool _exclusive = false;

        Text _text;

        std::function<void(bool)> _onClicked;

        std::shared_ptr<ButtonGroup> _buttonGroup;

        Rect _checkedRectangle;

    private:
        std::function<bool()> _judgeClick;
    };
}


#endif //GWUI_ABSTRACTBUTTON_H
