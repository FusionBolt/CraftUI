//
// Created by fusionbolt on 2020-02-06.
//

#ifndef GWUI_VERTICALLAYOUT_H
#define GWUI_VERTICALLAYOUT_H

#include "Widget.h"

namespace GWUI
{
    class VerticalLayout : public Widget
    {
    public:
        VerticalLayout() = default;

        void AddWidget(std::shared_ptr<Widget> widget);

        void SetGeometry(Rect rect) noexcept override;

    protected:
        void MousePressEvent(const MouseEvent &mouseEvent) override;

    private:
        Rect _f(size_t index);

        void _ResetWidgetsGeometry();

        size_t _rowMin = 0, _rowMax = 99;
    };
}

#endif //GWUI_VERTICALLAYOUT_H
