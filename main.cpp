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
#include "widget/VerticalLayout.h"

void LoadButton(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    auto button = std::make_shared<GWUI::Button>();
    auto objName = node.attribute("name").value();
    auto property = node.child("property");
    auto buttonText = property.child("string").child_value();
    auto xv = property.child("geometry").child("x").child_value();
    auto yv = property.child("geometry").child("y").child_value();
    auto wv = property.child("geometry").child("width").child_value();
    auto hv = property.child("geometry").child("height").child_value();
    button->SetParent(parent);
    button->SetText(buttonText);
    button->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
    button->SetObjectName(objName);
    button->OnClicked([=](bool){std::cout << "button:" << button->GetObjectName() << " On clicked" << std::endl;});
    auto rect = button->GetGeometry();
}

void LoadTextArea(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    auto textArea = std::make_shared<GWUI::TextArea>();
    auto objName = node.attribute("name").value();
    auto property = node.child("property");
    auto buttonText = node.child("property").child("string").child_value();
    auto xv = property.child("geometry").child("x").child_value();
    auto yv = property.child("geometry").child("y").child_value();
    auto wv = property.child("geometry").child("width").child_value();
    auto hv = property.child("geometry").child("height").child_value();
    textArea->SetParent(parent);
    textArea->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
    textArea->SetObjectName(objName);
}

void LoadComboBox(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    auto comboBox = std::make_shared<GWUI::ComboBox>();
    auto objName = node.attribute("name").value();
    comboBox->SetParent(parent);
    comboBox->SetObjectName(objName);
    std::vector<std::string> items;
    for (const auto &item : node.child("property").child("itemList"))
    {
        items.emplace_back(item.child_value());
    }
    comboBox->AddItems(items);
}

void LoadLabel(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    auto property = node.child("property");
    std::cout << std::stoi(property.child("geometry").child("x").child_value()) << std::endl;
    auto label = std::make_shared<GWUI::Label>(
            property.child("string").child_value());
    label->SetParent(parent);
    label->SetObjectName(node.attribute("name").value());
    label->SetFontSize(std::stoi(property.child("fontSize").child_value()));
    label->SetPosition({std::stoi(property.child("geometry").child("x").child_value()),
                        std::stoi(property.child("geometry").child("y").child_value())});
    label->SetFontColor({255, 255, 255});
}
std::shared_ptr<GWUI::VerticalLayout> LoadVerticalLayout(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{

}
void LoadXML(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    for (const auto &widgetNode : node.child("widget"))
    {
        std::map<std::string, std::function<std::shared_ptr<GWUI::Widget>(const pugi::xml_node&, std::shared_ptr<GWUI::Widget>)>> fun;
        auto s = std::invoke(fun[widgetNode.attribute("class").value()], widgetNode, parent);
        s->SetParent(parent);
        s->SetObjectName(node.attribute("name").value());
        LoadXML(widgetNode, s);
    }
}
void f()
{
    std::map<std::string, std::function<std::shared_ptr<GWUI::Widget>(const pugi::xml_node&, std::shared_ptr<GWUI::Widget>)>> fun;
    fun["s"] = LoadVerticalLayout;
}
int main()
{
    // GhostWhite
    // #F8F8FF
    GWUI::System system;
    auto w = std::make_shared<GWUI::Window>();

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("/Users/fusionbolt/CLionProjects/GWUI/test.xml");
    std::cout << "Load result: " << result.description() << std::endl;
    std::cout << doc.child("widget").attribute("class").value() << std::endl;

    LoadXML(doc, w);
    for (const auto &widget : doc.child("widget"))
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
            LoadComboBox(widget, w);
        }
        if (std::string(widget.attribute("class").value()) == "Label")
        {
            std::cout << "Load Label" << std::endl;
            LoadLabel(widget, w);
        }
    }
    auto pic = std::make_shared<GWUI::Label>();
    pic->SetParent(w);
    pic->SetPicture("/Users/fusionbolt/CLionProjects/GWUI/source/wz.png", {700, 500, 200, 200});

    auto label = w->FindChild<GWUI::Label>("textLabel");
    auto comboBox = w->FindChild<GWUI::ComboBox>("comboBox1");
    comboBox->OnChanged([=](const std::string &nowText)
                        { label->SetText(nowText); });

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

    // examine buttonGroup life cycle
    // destroyed when buttons are destroyed
    {
        auto buttonGroup = std::make_shared<GWUI::ButtonGroup>();

        auto checkBox1 = std::make_shared<GWUI::CheckBox>("checkBox1");
        //checkBox1->SetParent(w);
        checkBox1->SetObjectName("checkBox1");
        checkBox1->SetGeometry({420, 40, 120, 50});
        auto checkBox2 = std::make_shared<GWUI::CheckBox>("checkBox2");
        //checkBox2->SetParent(w);
        checkBox2->SetObjectName("checkBox2");
        checkBox2->SetGeometry({560, 40, 120, 50});
        auto checkBox3 = std::make_shared<GWUI::CheckBox>("checkBox3");
        //checkBox3->SetParent(w);
        checkBox3->SetObjectName("checkBox3");
        checkBox3->SetGeometry({420, 110, 120, 50});
        buttonGroup->AddButton(checkBox1);
        buttonGroup->AddButton(checkBox2);
        buttonGroup->AddButton(checkBox3);
        buttonGroup->RemoveButton(checkBox3);

        //TODO: 多个parent
        auto verticalLayout = std::make_shared<GWUI::VerticalLayout>();
        verticalLayout->SetGeometry({420, 40, 120, 150});
        verticalLayout->SetParent(w);
        verticalLayout->SetObjectName("verticalLayout");
        verticalLayout->AddWidget(checkBox1);
        verticalLayout->AddWidget(checkBox2);
        verticalLayout->AddWidget(checkBox3);
    }
    //TODO: 多级控件处理 创建与事件分发
    w->ShowAllChild();
    w->Show();
}
