//
// Created by fusionbolt on 2020-01-30.
//

#include "AbstractButton.h"

#include <utility>

GWUI::AbstractButton::AbstractButton(const std::string& text, GWUI::Widget *widget) :
    Widget(widget),_text(text)
{

}

bool GWUI::AbstractButton::IsChecked()
{
    return _checked;
}

std::string GWUI::AbstractButton::GetText()
{
    return _text.GetText();
}

void GWUI::AbstractButton::SetText(const std::string &text)
{
    _text.SetText(text);
}

bool GWUI::AbstractButton::IsCheckable()
{
    return _checkable;
}

void GWUI::AbstractButton::OnClick(std::function<void(bool)> f)
{
    _onClicked = std::move(f);
}
