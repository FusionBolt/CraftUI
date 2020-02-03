//
// Created by fusionbolt on 2020-01-30.
//

#ifndef GWUI_ABSTRACTBUTTON_H
#define GWUI_ABSTRACTBUTTON_H


#include "Widget.h"
#include "../units/Text.h"

namespace GWUI
{
    class AbstractButton : public Widget
    {
    public:
        explicit AbstractButton(const std::string& text = "button", Widget* widget = nullptr);

        bool IsChecked();

        // TODO:check or down??
        bool IsCheckable();

        std::string GetText();

        void SetText(const std::string& text);

        void OnClick(std::function<void(bool)> f);
        // TODO:need virtual event?
    protected:
        bool _checked = false;

        bool _checkable = true;

        Text _text;

        std::function<void(bool)> _onClicked;
    };
}


#endif //GWUI_ABSTRACTBUTTON_H
