//
// Created by fusionbolt on 2020-02-06.
//

#ifndef GWUI_VERTICALLAYOUT_H
#define GWUI_VERTICALLAYOUT_H

#include "WidgetLayout.h"

namespace GWUI
{
    class VerticalLayout : public WidgetLayout
    {
    public:
        VerticalLayout() = default;

    private:
        Rect _ComputeChildGeometry(size_t index) override;

    };
}

#endif //GWUI_VERTICALLAYOUT_H
