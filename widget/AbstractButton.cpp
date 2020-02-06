//
// Created by fusionbolt on 2020-01-30.
//

#include "AbstractButton.h"

#include <utility>

GWUI::AbstractButton::AbstractButton(const std::string& text) :
    Widget(),_text(text)
{

}

bool GWUI::AbstractButton::IsChecked() const noexcept
{
    return _checked;
}

std::string GWUI::AbstractButton::GetText() const
{
    return _text.GetText();
}

void GWUI::AbstractButton::SetText(const std::string &text)
{
    _text.SetText(text);
}

bool GWUI::AbstractButton::IsCheckable() const noexcept
{
    return _checkable;
}

void GWUI::AbstractButton::OnClick(std::function<void(bool)> f)
{
    _onClicked = std::move(f);
}

void GWUI::AbstractButton::_SetButtonGroup(std::shared_ptr<ButtonGroup> buttonGroup)
{
    _buttonGroup = buttonGroup;
}
