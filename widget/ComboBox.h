//
// Created by fusionbolt on 2020-01-25.
//

#ifndef GWUI_COMBOBOX_H
#define GWUI_COMBOBOX_H

#include <string>
#include <vector>

#include "../units/Rectangle.h"
#include "../units/Text.h"
#include "Widget.h"

namespace Craft
{
    class ComboBox : public Widget
    {
    public:
        ComboBox();

        void AddItems(const std::vector<std::string>& items);

        void AddItem(const std::string& item);

        void ClearItems();

        void Draw(Renderer &renderer) override;

        void OnChanged(std::function<void(const std::string&)> f);

        void SetGeometry(Rect rect) noexcept override;

    protected:
        void MousePressEvent(const MouseEvent &mouseEvent) override;

    private:
        Rect _GetListRectangle();

        bool _clickOnButtonArea(Point position);

        bool _clickOnItems(Point position);

        size_t _GetItemIndexFromPosition(Point position);

        int _height, _width; // declare early, other member initialization need this

        std::vector<Text> _items;

        Text _currentText;

        Rectangle _mainRectangle, _buttonRectangle;

        std::size_t _currentStringIndex = 0;

        bool _showList = false;

        std::function<void(const std::string&)> _onChanged;
    };
}

#endif //GWUI_COMBOBOX_H
