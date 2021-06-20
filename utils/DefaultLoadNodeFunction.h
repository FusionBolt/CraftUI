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
#include "../Layout/VerticalLayout.h"
#include "../widget/CheckBox.h"
#include "../widget/LineEdit.h"
#include "../widget/HorizontalSlider.h"
#include "../widget/Window.h"
#include "../Layout/HorizontalLayout.h"

namespace GWUI
{
    using ObjectPtr = std::shared_ptr<GWUI::Object>;

    // TODO:继承能否提取做法？？
    // TODO:不存在则设定默认值
    inline ObjectPtr LoadButton(const pugi::xml_node& node)
    {
        auto button = std::make_shared<GWUI::Button>();
        auto property = node.child("property");
        auto buttonText = property.child_value("string");
        button->SetText(buttonText);
        button->OnClicked([=](bool){std::cout << "OnClick:" << button->GetObjectName() << std::endl;});
        return button;
    }

    inline ObjectPtr LoadTextArea(const pugi::xml_node& node)
    {
        auto textArea = std::make_shared<GWUI::TextArea>();
        return textArea;
    }

    inline ObjectPtr LoadComboBox(const pugi::xml_node& node)
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

    inline ObjectPtr LoadLabel(const pugi::xml_node& node)
    {
        auto label = std::make_shared<GWUI::Label>();
        auto property = node.child("property");
        if (auto img = property.child("image"))
        {
            label->SetPicture(Image(img.child_value("path")));
        }
        else
        {
            label->SetText(property.child_value("string"));
            label->SetFontSize(std::stoi(property.child_value("fontSize")));
            label->SetPosition({std::stoi(property.child("geometry").child_value("x")),
                                std::stoi(property.child("geometry").child_value("y"))});
        }
        return label;
    }

    inline ObjectPtr LoadVerticalLayout(const pugi::xml_node& node)
    {
        auto verticalLayout = std::make_shared<GWUI::VerticalLayout>();
        auto property = node.child("property");
        if (auto geometry = property.child("geometry");geometry != nullptr)
        {
            auto xv = geometry.child_value("x");
            auto yv = geometry.child_value("y");
            auto wv = geometry.child_value("width");
            auto hv = geometry.child_value("height");
            verticalLayout->SetGeometry(
                    {std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)}
            );
        }
        return verticalLayout;
    }

    inline ObjectPtr LoadHorizontalLayout(const pugi::xml_node& node)
    {
        auto horizontalLayout = std::make_shared<GWUI::HorizontalLayout>();
        auto property = node.child("property");
        if (auto geometry = property.child("geometry");geometry != nullptr)
        {
            auto xv = geometry.child_value("x");
            auto yv = geometry.child_value("y");
            auto wv = geometry.child_value("width");
            auto hv = geometry.child_value("height");
            horizontalLayout->SetGeometry(
                    {std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)}
            );
        }
        return horizontalLayout;
    }

    inline ObjectPtr LoadCheckBox(const pugi::xml_node& node)
    {
        auto checkBox = std::make_shared<GWUI::CheckBox>();
        auto property = node.child("property");
        checkBox->SetText(property.child("string").child_value());
        if(auto exclusive = property.child("exclusive"); exclusive)
        {
            checkBox->SetExclusive(std::string(exclusive.child_value()) == "true");
        }
        return checkBox;
    }

    inline ObjectPtr LoadLineEdit(const pugi::xml_node& node)
    {
        auto lineEdit = std::make_shared<GWUI::LineEdit>();
        return lineEdit;
    }

    inline ObjectPtr LoadHorizontalSlider(const pugi::xml_node& node)
    {
        auto horizontalSlider = std::make_shared<GWUI::HorizontalSlider>();
        horizontalSlider->SetTestMove(false);
        if (auto min = node.child("property").child("range").child_value("min"),
                max = node.child("property").child("range").child_value("max");
            min && max)
        {
            std::cout << "slider:" << std::stoi(min) << " " << std::stoi(max) << std::endl;
            horizontalSlider->SetValueRange(std::stoi(min), std::stoi(max));
        }
        return horizontalSlider;
    }

    inline ObjectPtr LoadWindow(const pugi::xml_node& node)
    {
        auto window = std::make_shared<GWUI::Window>();
        auto property = node.child("property");
        window->SetWindowTitle(property.child_value("title"));
        auto width = std::stoi(property.child("geometry").child_value("width"));
        auto height = std::stoi(property.child("geometry").child_value("height"));
        window->SetWindowSize(width, height);
        return window;
    }
}

#endif //GWUI_DEFAULTLOADNODEFUNCTION_H
