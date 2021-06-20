//
// Created by fusionbolt on 2020/3/16.
//

#include "WidgetLayout.h"

void GWUI::WidgetLayout::SetGeometry(GWUI::Rect rect) noexcept
{
    _rect = rect;
    _ResetWidgetsGeometry();
}

void GWUI::WidgetLayout::AddChild(std::shared_ptr <Object> &child)
{
    child->SetParent(std::dynamic_pointer_cast<Object>(shared_from_this()));
    _ResetWidgetsGeometry();
}

void GWUI::WidgetLayout::_ResetWidgetsGeometry()
{
    size_t index = 0;
    for(auto& child : _childs)
    {
        std::dynamic_pointer_cast<Widget>(child)->SetGeometry(_ComputeChildGeometry(index++));
    }
}
