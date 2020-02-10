//
// Created by fusionbolt on 2020-02-07.
//

#include "XMLLoad.h"
#include "DefaultLoadNodeFunction.h"

void GWUI::XMLLoad::RegisterLoadFun(const std::string& className, GWUI::XMLLoad::FunctionType function)
{
    _loadFun[className] = std::move(function);
}

GWUI::XMLLoad::XMLLoad(const std::string &path)
{
    // TODO:加载失败，路径不存在的处理
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if(result)
    {
    std::cout << "XML Load result:" << result.description() << std::endl;
    }
    else
    {
        std::cout << "XML Load failed" << std::endl;
    }
    _InitLoadFun();
    std::cout << doc.child("widget").attribute("name").value() << "!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << doc.child("widget").attribute("class").value() << "!!!!!!!!!!!!!!!!!!!" << std::endl;
}

void GWUI::XMLLoad::_InitLoadFun()
{
    RegisterLoadFun("Button", LoadButton);
    RegisterLoadFun("TextArea", LoadTextArea);
    RegisterLoadFun("ComboBox", LoadComboBox);
    RegisterLoadFun("Label", LoadLabel);
    RegisterLoadFun("VerticalLayout", LoadVerticalLayout);
    RegisterLoadFun("CheckBox", LoadCheckBox);
    RegisterLoadFun("LineEdit", LoadLineEdit);
    RegisterLoadFun("HorizontalSlider", LoadHorizontalSlider);
    RegisterLoadFun("Window", LoadWindow);
}

void GWUI::XMLLoad::Analysis()
{
    // _LoadXMLNode(doc, nullptr);
    std::cout << "load start" << std::endl;
    _LoadXMLNode(doc, nullptr);
    std::cout << "load end" << std::endl;
}

void GWUI::XMLLoad::_LoadXMLNode(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    for(const auto &widgetNode : node.children("widget"))
    {
        auto className = std::string(widgetNode.attribute("class").value());

        std::cout << "class:" << widgetNode.attribute("class").value() << std::endl;
        std::cout << "obj name:" << widgetNode.attribute("name").value() << std::endl;
        std::cout << "node Name:" << widgetNode.name() << " node value:" << widgetNode.value() << std::endl;

        auto s = std::invoke(_loadFun[className], widgetNode);
        if(std::string(widgetNode.parent().attribute("class").value()) == "VerticalLayout")
        {
            std::dynamic_pointer_cast<VerticalLayout>(parent)->AddWidget(s);
        }
        else
        {
            s->SetParent(parent);
        }
        s->SetObjectName(widgetNode.attribute("name").value());

        auto property = widgetNode.child("property");
        if (auto geometry = property.child("geometry");geometry != nullptr)
        {
            auto xv = geometry.child_value("x");
            auto yv = geometry.child_value("y");
            auto wv = geometry.child_value("width");
            auto hv = geometry.child_value("height");
            s->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
        }
        _LoadXMLNode(widgetNode, s);
        if(className == "Window")
        {
            _window = std::dynamic_pointer_cast<GWUI::Window>(s);
        }
    }
}

std::shared_ptr<GWUI::Window> GWUI::XMLLoad::GetWindow()
{
    return _window;
}
