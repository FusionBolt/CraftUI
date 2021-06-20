//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_XMLLOAD_H
#define GWUI_XMLLOAD_H

#include <map>
#include <pugixml.hpp>

#include "../widget/Widget.h"
#include "../widget/Window.h"

namespace GWUI
{
    class XMLLoad
    {
    public:
        using FunctionType = std::function<std::shared_ptr<GWUI::Object>(const pugi::xml_node&)>;

        XMLLoad(const std::string& path);

        void RegisterLoadFun(const std::string& className, FunctionType function);

        void Analysis();

        template<typename T>
        std::shared_ptr<T> GetRoot()
        {
            static_assert(std::is_base_of_v<GWUI::Widget, T>, "T should is base of GWUI::Widget");
            return std::dynamic_pointer_cast<T>(_window);
        }

    private:
        void _InitLoadFun();

        void _LoadXMLNode(const pugi::xml_node& node, const std::shared_ptr<Object> &parent);

        std::map<std::string, FunctionType> _loadFun;

        pugi::xml_document doc;

        std::shared_ptr<GWUI::Widget> _window;
    };
}

#endif //GWUI_XMLLOAD_H
