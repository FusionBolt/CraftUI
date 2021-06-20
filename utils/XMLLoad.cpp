//
// Created by fusionbolt on 2020-02-07.
//

#include "XMLLoad.h"
#include "DefaultLoadNodeFunction.h"
#include "../widget/ButtonGroup.h"
#include "../core/MetaInfo.h"

void GWUI::XMLLoad::RegisterLoadFun(const std::string& className, GWUI::XMLLoad::FunctionType function)
{
    _loadFun[className] = std::move(function);
}

GWUI::XMLLoad::XMLLoad(const std::string &path)
{
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    if (!result)
    {
        throw "XML LoadFailed";
    }
    _InitLoadFun();
    std::cout << "Fun Load Successful" << std::endl;
}

void GWUI::XMLLoad::_InitLoadFun()
{
    RegisterLoadFun("Button", LoadButton);
    RegisterLoadFun("TextArea", LoadTextArea);
    RegisterLoadFun("ComboBox", LoadComboBox);
    RegisterLoadFun("Label", LoadLabel);
    RegisterLoadFun("VerticalLayout", LoadVerticalLayout);
    RegisterLoadFun("HorizontalLayout", LoadHorizontalLayout);
    RegisterLoadFun("CheckBox", LoadCheckBox);
    RegisterLoadFun("LineEdit", LoadLineEdit);
    RegisterLoadFun("HorizontalSlider", LoadHorizontalSlider);
    RegisterLoadFun("Window", LoadWindow);
}

void GWUI::XMLLoad::Analysis()
{
    _LoadXMLNode(doc, nullptr);
    std::cout << "XML Load end" << std::endl;
}

void GWUI::XMLLoad::_LoadXMLNode(const pugi::xml_node& node, const std::shared_ptr<Object> &parent)
{
    auto buttonGroup = std::make_shared<ButtonGroup>();
    for (const auto &objectNode : node.children("widget"))
    {
        // 通用属性 继承自widget
        auto className = std::string(objectNode.attribute("class").value());
        auto object = std::invoke(_loadFun[className], objectNode);

        //auto parentClassName = std::string(node.parent().attribute("class").value());
        std::string parentClassName;
        if (parent == nullptr)
        {
            parentClassName = "null";
        }
        else
        {
            parentClassName = parent->GetClassName();
        }


        if (IsLayout(parentClassName))
        {
            if (IsWidget(className) || IsLayout(className))
            {
                std::dynamic_pointer_cast<WidgetLayout>(parent)->AddChild(object);
            }
        }
        else
        {
            object->SetParent(parent);
        }

        if (IsButton(className))
        {
            auto button = std::dynamic_pointer_cast<AbstractButton>(object);
            if (button->IsExclusive())
            {
                buttonGroup->AddButton(button);
            }
        }

        if (IsLayout(className))
        {
            std::cout << "layout" << std::endl;
        }

        object->SetClassName(className);
        object->SetObjectName(objectNode.attribute("name").value());

        if (IsWidget(className))
        {
            auto widget = std::dynamic_pointer_cast<Widget>(object);
            auto property = objectNode.child("property");
            if (auto geometry = property.child("geometry");geometry != nullptr)
            {
                auto xv = geometry.child_value("x");
                auto yv = geometry.child_value("y");
                auto wv = geometry.child_value("width");
                auto hv = geometry.child_value("height");
                widget->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});
            }
        }

        _LoadXMLNode(objectNode, object);

        // TODO:特殊情况处理
        if (className == "Window")
        {
            _window = std::dynamic_pointer_cast<GWUI::Window>(object);
        }
    }
}
template<typename T1, typename T2>
constexpr bool f(std::shared_ptr<T1>)
{
    return std::is_convertible_v<T1, T2>;
}