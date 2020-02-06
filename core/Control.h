//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_CONTROL_H
#define GWUI_CONTROL_H

#include "../widget/Widget.h"

namespace GWUI
{
    class Control
    {
    public:
        void SetFocusWidget(Widget::Ptr widge);

        int EventDispatch(CrudeEvent event, Widget::Ptr widget);

    private:
        Widget::Ptr _currentFocusWidget;
    };
}

#endif //GWUI_CONTROL_H
