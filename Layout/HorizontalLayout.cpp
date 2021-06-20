//
// Created by fusionbolt on 2020/3/16.
//

#include "HorizontalLayout.h"

GWUI::Rect GWUI::HorizontalLayout::_ComputeChildGeometry(size_t index)
{
    auto widgetCount = _childs.size();
    auto rect = _rect;
    rect.w /= widgetCount;
    rect.x += static_cast<int>(index) * rect.w;
    return rect;
}