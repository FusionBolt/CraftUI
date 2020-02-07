//
// Created by fusionbolt on 2020-02-07.
//

#include "XMLLoad.h"

void GWUI::XMLLoad::RegisterLoadFun(const std::string& className, GWUI::XMLLoad::FunctionType function)
{
    _loadFun[className] = std::move(function);
}

GWUI::XMLLoad::XMLLoad(const std::string &path)
{
    // TODO:加载失败，路径不存在的处理
    pugi::xml_parse_result result = doc.load_file(path.c_str());
    std::cout << "XML Load result:" << result.description() << std::endl;
}

void GWUI::XMLLoad::_InitLoadFun()
{
    RegisterLoadFun();
}

void GWUI::XMLLoad::Analysis(std::shared_ptr<GWUI::Widget> parent)
{
    // _LoadXMLNode(doc, nullptr);
    _LoadXMLNode(doc.child("widget"), parent);
}

void GWUI::XMLLoad::_LoadXMLNode(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget> parent)
{
    for (const auto &widgetNode : node.child("widget"))
    {
        auto s = std::invoke(_loadFun[widgetNode.attribute("class").value()], widgetNode);
        s->SetParent(parent);
        s->SetObjectName(node.attribute("name").value());

        auto property = node.child("property");
        auto xv = property.child("geometry").child("x").child_value();
        auto yv = property.child("geometry").child("y").child_value();
        auto wv = property.child("geometry").child("width").child_value();
        auto hv = property.child("geometry").child("height").child_value();
        s->SetGeometry({std::stoi(xv), std::stoi(yv), std::stoi(wv), std::stoi(hv)});

        _LoadXMLNode(widgetNode, s);
    }
}
