//
// Created by fusionbolt on 2020-02-06.
//

#include "VerticalLayout.h"

void GWUI::VerticalLayout::AddWidget(std::shared_ptr<Widget> widget)
{
    widget->SetParent(std::dynamic_pointer_cast<Widget>(shared_from_this()));
    std::cout << "push child size:" << _childs.size() << std::endl;
    _ResetWidgetsGeometry();
}

void GWUI::VerticalLayout::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _ResetWidgetsGeometry();
}

GWUI::Rect GWUI::VerticalLayout::_f(size_t index)
{
    auto widgetCount = _childs.size();
    auto rect = GetGeometry();
    rect.h /= widgetCount;
    rect.y += static_cast<int>(index) * rect.h;
    return rect;
}

void GWUI::VerticalLayout::_ResetWidgetsGeometry()
{
    size_t index = 0;
    for(auto& child : _childs)
    {
        child->SetGeometry(_f(index++));
    }
}

void GWUI::VerticalLayout::MousePressEvent(const GWUI::MouseEvent &mouseEvent)
{
    Widget::MousePressEvent(mouseEvent);
}
