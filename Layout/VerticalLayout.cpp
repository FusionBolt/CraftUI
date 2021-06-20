//
// Created by fusionbolt on 2020-02-06.
//

#include "VerticalLayout.h"

GWUI::Rect GWUI::VerticalLayout::_ComputeChildGeometry(size_t index)
{
    auto widgetCount = _childs.size();
    auto rect = _rect;
    rect.h /= widgetCount;
    rect.y += static_cast<int>(index) * rect.h;
    return rect;
}