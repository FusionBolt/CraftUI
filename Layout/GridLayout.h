//
// Created by fusionbolt on 2020/3/16.
//

#ifndef GWUI_GRIDLAYOUT_H
#define GWUI_GRIDLAYOUT_H


#include "../widget/Widget.h"

namespace GWUI
{
    class GridLayout : public Widget
    {
    public:
        GridLayout() = default;

        void AddWidget(std::shared_ptr<Widget>& widget, size_t row, size_t col);

    private:
        virtual Rect _ComputeChildGeometry(size_t index) = 0;

        virtual void _ResetWidgetsGeometry() = 0;

        std::vector<std::vector<std::weak_ptr<Widget>>> _widgets;

        Rect _rect;
    };
}


#endif //GWUI_GRIDLAYOUT_H
