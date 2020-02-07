//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_XMLLOAD_H
#define GWUI_XMLLOAD_H

#include <map>

#include "pugixml.hpp"
#include "../widget/Widget.h"

namespace GWUI
{
    class XMLLoad
    {
    public:
        using FunctionType = std::function<std::shared_ptr<GWUI::Widget>(const pugi::xml_node&)>;

        XMLLoad(const std::string& path);

        void RegisterLoadFun(const std::string& className, FunctionType function);

        void Analysis(std::shared_ptr<GWUI::Widget> parent);

    private:
        void _InitLoadFun();

        void _LoadXMLNode(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget>);

        std::map<std::string, FunctionType> _loadFun;

        pugi::xml_document doc;
    };
}

#endif //GWUI_XMLLOAD_H
