//
// Created by fusionbolt on 2020/3/16.
//

#ifndef GWUI_WIDGETLAYOUT_H
#define GWUI_WIDGETLAYOUT_H


#include "../widget/Widget.h"

namespace GWUI
{
    class WidgetLayout : public Object
    {
    public:
        WidgetLayout() = default;
        // TODO:总觉得名字不太合适
        void AddChild(std::shared_ptr<Object>& child);
        // TODO:rename
        void SetGeometry(Rect rect) noexcept;

    protected:
        virtual Rect _ComputeChildGeometry(size_t index) = 0;

        void _ResetWidgetsGeometry();

        Rect _rect;
    };
}


#endif //GWUI_WIDGETLAYOUT_H
