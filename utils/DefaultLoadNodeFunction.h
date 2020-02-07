//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_DEFAULTLOADNODEFUNCTION_H
#define GWUI_DEFAULTLOADNODEFUNCTION_H

#include <pugixml.hpp>
#include "../widget/Widget.h"
#include "../widget/Button.h"
#include "../widget/TextArea.h"
#include "../widget/ComboBox.h"
#include "../widget/Label.h"
#include "../widget/VerticalLayout.h"

namespace GWUI
{
    using WidgetPtr = std::shared_ptr<GWUI::Widget>;

    inline WidgetPtr LoadButton(const pugi::xml_node& node)
    {
        auto button = std::make_shared<GWUI::Button>();
        auto property = node.child("property");
        auto buttonText = property.child("string").child_value();
        button->SetText(buttonText);
        return button;
    }

    inline WidgetPtr LoadTextArea(const pugi::xml_node& node)
    {
        auto textArea = std::make_shared<GWUI::TextArea>();
        return textArea;
    }

    inline WidgetPtr LoadComboBox(const pugi::xml_node& node)
    {
        auto comboBox = std::make_shared<GWUI::ComboBox>();
        std::vector<std::string> items;
        for (const auto &item : node.child("property").child("itemList"))
        {
            items.emplace_back(item.child_value());
        }
        comboBox->AddItems(items);
        return comboBox;
    }

    inline WidgetPtr LoadLabel(const pugi::xml_node& node)
    {
        auto label = std::make_shared<GWUI::Label>();
        auto property = node.child("property");
        label->SetText(property.child("string").child_value());
        label->SetFontSize(std::stoi(property.child("fontSize").child_value()));
        label->SetPosition({std::stoi(property.child("geometry").child("x").child_value()),
                            std::stoi(property.child("geometry").child("y").child_value())});
        label->SetFontColor({255, 255, 255});
        return label;
    }

    inline WidgetPtr LoadVerticalLayout(const pugi::xml_node& node)
    {
        auto verticalLayout = std::make_shared<GWUI::VerticalLayout>();
        return verticalLayout;
    }
}

#endif //GWUI_DEFAULTLOADNODEFUNCTION_H
