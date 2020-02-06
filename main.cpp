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
#include "widget/ButtonGroup.h"

void LoadButton(const pugi::xml_node& buttonNode, std::shared_ptr<GWUI::Widget> parent)
{
    auto button = std::make_shared<GWUI::Button>();
    auto objName = buttonNode.attribute("name").value();
    auto property = buttonNode.child("property");
    auto buttonText = property.child("string").child_value();
    auto xv = property.child("geometry").child("x").child_value();
    auto yv = property.child("geometry").child("y").child_value();
    auto wv = property.child("geometry").child("width").child_value();
    auto hv = property.child("geometry").child("height").child_value();
    button->SetParent(parent);
    button->SetText(buttonText);
    button->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
    button->SetObjectName(objName);
    button->OnClicked([=](){std::cout << "button:" << button->GetObjectName() << " On clicked" << std::endl;});
    auto rect = button->GetGeometry();
}

void LoadTextArea(const pugi::xml_node& buttonNode, std::shared_ptr<GWUI::Widget> parent)
{
    auto textArea = std::make_shared<GWUI::TextArea>();
    auto objName = buttonNode.attribute("name").value();
    auto property = buttonNode.child("property");
    auto buttonText = buttonNode.child("property").child("string").child_value();
    auto xv = property.child("geometry").child("x").child_value();
    auto yv = property.child("geometry").child("y").child_value();
    auto wv = property.child("geometry").child("width").child_value();
    auto hv = property.child("geometry").child("height").child_value();
    textArea->SetParent(parent);
    textArea->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
    textArea->SetObjectName(objName);
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

    for(const auto& widget : doc.child("widget"))
    {
        std::cout << "Load widgets: " << widget.attribute("name").value() << std::endl;
        if (std::string(widget.attribute("class").value()) == "Button")
        {
            std::cout << "Load widget" << std::endl;
            LoadButton(widget, w);
        }
        if (std::string(widget.attribute("class").value()) == "TextArea")
        {
            std::cout << "Load textArea" << std::endl;
            LoadTextArea(widget, w);
        }
        if (std::string(widget.attribute("class").value()) == "ComboBox")
        {
            std::cout << "Load ComboBox" << std::endl;
            auto comboBox = std::make_shared<GWUI::ComboBox>();
            auto objName = widget.attribute("name").value();
            comboBox->SetParent(w);
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
            std::cout << "Load Label" << std::endl;
            auto property = widget.child("property");
            std::cout << std::stoi(property.child("geometry").child("x").child_value()) << std::endl;
            auto label = std::make_shared<GWUI::Label>(
                                    property.child("string").child_value());
            label->SetParent(w);
            label->SetObjectName(widget.attribute("name").value());
            label->SetFontSize(std::stoi(property.child("fontSize").child_value()));
            label->SetPosition({std::stoi(property.child("geometry").child("x").child_value()),
                                std::stoi(property.child("geometry").child("y").child_value())});
            label->SetFontColor({255, 255, 255});
        }
    }
    auto pic = std::make_shared<GWUI::Label>();
    pic->SetParent(w);
    pic->SetPicture("/Users/fusionbolt/CLionProjects/GWUI/source/wz.png", {700, 500, 200, 200});

    auto label = w->FindChild<GWUI::Label>("textLabel");
    auto comboBox = w->FindChild<GWUI::ComboBox>("comboBox1");
    comboBox->OnChanged([=](const std::string& nowText){label->SetText(nowText);});

    auto h1 = std::make_shared<GWUI::HorizontalSlider>();
    h1->SetParent(w);
    h1->SetObjectName("h1");
    h1->SetGeometry({300, 300, 150, 20});
    auto h2 = std::make_shared<GWUI::HorizontalSlider>();
    h2->SetParent(w);
    h2->SetObjectName("h2");
    h2->SetGeometry({300, 500, 150, 20});
    h2->SetValueRange(50, 150);

    auto lineEdit = std::make_shared<GWUI::LineEdit>();
    lineEdit->SetParent(w);
    lineEdit->SetObjectName("h1");
    lineEdit->SetGeometry({300, 700, 100, 25});

    auto checkBox = std::make_shared<GWUI::CheckBox>("checkBox");
    checkBox->SetParent(w);
    checkBox->SetObjectName("checkBox");
    checkBox->SetGeometry({500, 600, 100, 100});

    auto buttonGroup = std::make_shared<GWUI::ButtonGroup>();

    auto checkBox1 = std::make_shared<GWUI::CheckBox>("checkBox1");
    checkBox1->SetParent(w);
    checkBox1->SetObjectName("checkBox1");
    checkBox1->SetGeometry({420, 40, 120, 50});
    auto checkBox2 = std::make_shared<GWUI::CheckBox>("checkBox2");
    checkBox2->SetParent(w);
    checkBox2->SetObjectName("checkBox2");
    checkBox2->SetGeometry({560, 40, 120, 50});
    auto checkBox3 = std::make_shared<GWUI::CheckBox>("checkBox3");
    checkBox3->SetParent(w);
    checkBox3->SetObjectName("checkBox3");
    checkBox3->SetGeometry({420, 110, 120, 50});
    buttonGroup->AddButton(checkBox1);
    buttonGroup->AddButton(checkBox2);
    buttonGroup->AddButton(checkBox3);
    buttonGroup->RemoveButton(checkBox3);

    w->ShowAllChild();
    w->Show();
}
