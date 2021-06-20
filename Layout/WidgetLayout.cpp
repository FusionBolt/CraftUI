//
// Created by fusionbolt on 2020/3/16.
//

#include "WidgetLayout.h"

void Craft::WidgetLayout::SetGeometry(Craft::Rect rect) noexcept
{
    _rect = rect;
    _ResetWidgetsGeometry();
}

void Craft::WidgetLayout::AddChild(std::shared_ptr <Object> &child)
{
    child->SetParent(std::dynamic_pointer_cast<Object>(shared_from_this()));
    _ResetWidgetsGeometry();
}

void Craft::WidgetLayout::_ResetWidgetsGeometry()
{
    size_t index = 0;
    for(auto& child : _childs)
    {
        std::dynamic_pointer_cast<Widget>(child)->SetGeometry(_ComputeChildGeometry(index++));
    }
}
