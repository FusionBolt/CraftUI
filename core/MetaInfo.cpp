//
// Created by fusionbolt on 2020/3/20.
//

#include "MetaInfo.h"

#include <vector>

// TODO:constexpr C++20
std::vector<std::string> LayoutClass = {"WidgetLayout", "HorizontalLayout", "VerticalLayout", "GridLayout"};

std::vector<std::string> ButtonClass = {"AbstractButton", "Button", "CheckBox"};

bool Craft::IsLayout(const std::string &className)
{
    return std::find(LayoutClass.begin(), LayoutClass.end(), className) != LayoutClass.end();
}

bool Craft::IsButton(const std::string &className)
{
    return std::find(ButtonClass.begin(), ButtonClass.end(), className) != ButtonClass.end();
}

// TODO:日后改进
bool Craft::IsWidget(const std::string &className)
{
    return !(IsLayout(className) || className == "ButtonGroup");
}

bool Craft::IsSingleObject(const std::string &className)
{
    return IsWidget(className);
}

