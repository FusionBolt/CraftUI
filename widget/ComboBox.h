//
// Created by fusionbolt on 2020-01-25.
//

#ifndef GWUI_COMBOBOX_H
#define GWUI_COMBOBOX_H

#include <string>
#include <vector>

#include "../units/Rectangle.hpp"
#include "../units/Text.h"
#include "Widget.h"

namespace GWUI
{
    class ComboBox : public Widget
    {
    public:
        ComboBox(Widget* parent);

        void AddItems(const std::vector<std::string>& items);
        // need &&
        // void AddItems(std::vector<std::string>&& items);

        void AddItem(const std::string& item);

        void AddItem(std::string&& item);

        void Draw(Renderer renderer) override;

        void OnChanged(std::function<void(const std::string&)> f);

    protected:
        void MousePressEvent(const MouseEvent &mouseEvent) override;

    private:
        int _height; // declare early, other member initialization need this

        std::vector<Text> _items;

        Text _currentText;

        Rectangle _mainRectangle, _buttonRectangle, _listRectangle;

        std::size_t _currentStringIndex;

        bool _showList;

        std::function<void(const std::string&)> _onChanged;
    };
}

#endif //GWUI_COMBOBOX_H
