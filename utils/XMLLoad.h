//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_XMLLOAD_H
#define GWUI_XMLLOAD_H

#include <map>

#include "pugixml.hpp"
#include "../widget/Widget.h"
#include "../widget/Window.h"

namespace GWUI
{
    class XMLLoad
    {
    public:
        using FunctionType = std::function<std::shared_ptr<GWUI::Widget>(const pugi::xml_node&)>;

        XMLLoad(const std::string& path);

        void RegisterLoadFun(const std::string& className, FunctionType function);

        void Analysis();

        std::shared_ptr<GWUI::Window> GetWindow();

    private:
        void _InitLoadFun();

        void _LoadXMLNode(const pugi::xml_node& node, std::shared_ptr<GWUI::Widget>);

        std::map<std::string, FunctionType> _loadFun;

        pugi::xml_document doc;
        // TODO:document与node类型不同

        std::shared_ptr<GWUI::Window> _window;
    };
}

#endif //GWUI_XMLLOAD_H
