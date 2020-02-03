#include <iostream>
#include <map>

#include "widget/Window.h"
#include "core/System.hpp"
#include "widget/Button.h"

#include "pugixml.hpp"
#include "widget/TextArea.h"
#include "widget/ComboBox.h"
#include "widget/Label.h"
#include "widget/HorizontalSlider.h"
#include "widget/LineEdit.h"
#include "widget/CheckBox.h"

void LoadButton(const pugi::xml_node& buttonNode, GWUI::Button* button)
{
    auto objName = buttonNode.attribute("name").value();
    auto property = buttonNode.child("property");
    auto buttonText = property.child("string").child_value();
    auto xv = property.child("geometry").child("x").child_value();
    auto yv = property.child("geometry").child("y").child_value();
    auto wv = property.child("geometry").child("width").child_value();
    auto hv = property.child("geometry").child("height").child_value();
    button->SetText(buttonText);
    button->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
    button->SetObjectName(objName);
    button->OnClicked([=](){std::cout << "button:" << button->GetObjectName() << " On clicked" << std::endl;});
    auto rect = button->GetGeometry();
}

void LoadTextArea(const pugi::xml_node& buttonNode, GWUI::TextArea* textArea)
{
    auto objName = buttonNode.attribute("name").value();
    auto property = buttonNode.child("property");
    auto buttonText = buttonNode.child("property").child("string").child_value();
    auto xv = property.child("geometry").child("x").child_value();
    auto yv = property.child("geometry").child("y").child_value();
    auto wv = property.child("geometry").child("width").child_value();
    auto hv = property.child("geometry").child("height").child_value();
    // textArea->SetText(buttonText);
    textArea->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
    textArea->SetObjectName(objName);
    // textArea->OnClicked([=](){std::cout << "button:" << textArea->GetObjectName() << " On clicked" << std::endl;});
}

int main()
{
//    // GhostWhite
//    // #F8F8FF
//
    GWUI::System system;
    auto w = std::make_shared<GWUI::Window>();

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("/Users/fusionbolt/CLionProjects/GWUI/test.xml");
    std::cout << "Load result: " << result.description() << std::endl;
    std::cout << doc.child("widget").attribute("class").value() << std::endl;

    GWUI::Label* label = nullptr;
    GWUI::ComboBox* comboBox = nullptr;
    for(const auto& widget : doc.child("widget"))
    {
        std::cout << "Load widgets: " << widget.attribute("name").value() << std::endl;
        if (std::string(widget.attribute("class").value()) == "Button")
        {
            std::cout << "load widget" << std::endl;
            auto *button = new GWUI::Button(w.get());
            LoadButton(widget, button);
        }
        if (std::string(widget.attribute("class").value()) == "TextArea")
        {
            std::cout << "load textArea" << std::endl;
            auto *textArea = new GWUI::TextArea(w.get());
            LoadTextArea(widget, textArea);
        }
        if (std::string(widget.attribute("class").value()) == "ComboBox")
        {
            std::cout << "load ComboBox" << std::endl;
            comboBox = new GWUI::ComboBox(w.get());
            auto objName = widget.attribute("name").value();
            comboBox->SetObjectName(objName);
            std::vector<std::string> items;
            for (const auto &item : widget.child("property").child("itemList"))
            {
                items.emplace_back(item.child_value());
            }
            comboBox->AddItems(items);
        }
        if (std::string(widget.attribute("class").value()) == "Label")
        {
            std::cout << "load Label" << std::endl;
            auto property = widget.child("property");
            std::cout << std::stoi(property.child("geometry").child("x").child_value()) << std::endl;
            label = new GWUI::Label(w.get(),
                                    property.child("string").child_value());
            label->SetFontSize(std::stoi(property.child("fontSize").child_value()));
            label->SetPosition({std::stoi(property.child("geometry").child("x").child_value()),
                                std::stoi(property.child("geometry").child("y").child_value())});
            label->SetFontColor({255, 255, 255});
        }
    }

    auto* pic = new GWUI::Label(w.get());
    pic->SetPicture("/Users/fusionbolt/CLionProjects/GWUI/source/wz.png", {700, 500, 200, 200});

    comboBox->OnChanged([=](const std::string& nowText){label->SetText(nowText);});

    auto* h1 = new GWUI::HorizontalSlider(w.get());
    h1->SetObjectName("h1");
    h1->SetGeometry({300, 300, 150, 20});
    std::cout << "h1 x:" << h1->GetGeometry().x << std::endl;
    auto* h2 = new GWUI::HorizontalSlider(w.get());
    h2->SetObjectName("h2");
    h2->SetGeometry({300, 500, 150, 20});
    h2->SetValueRange(50, 150);

    auto* lineEdit = new GWUI::LineEdit(w.get());
    lineEdit->SetObjectName("h1");
    lineEdit->SetGeometry({300, 700, 100, 25});

    auto* checkBox = new GWUI::CheckBox("checkBox", w.get());
    checkBox->SetGeometry({500, 600, 100, 100});
    w->Show();
}
