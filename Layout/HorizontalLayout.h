//
// Created by fusionbolt on 2020/3/16.
//

#ifndef GWUI_HORIZONTALLAYOUT_H
#define GWUI_HORIZONTALLAYOUT_H

#include "WidgetLayout.h"

namespace Craft
{
    class HorizontalLayout : public WidgetLayout
    {
    public:
        HorizontalLayout() = default;

    private:
        Rect _ComputeChildGeometry(size_t index) override;

    };
}

#endif //GWUI_HORIZONTALLAYOUT_H
