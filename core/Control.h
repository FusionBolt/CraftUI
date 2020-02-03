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
        void SetFocusWidget(Widget* widge);

        int EventDispatch(CrudeEvent event, Widget* widget);

    private:
        Widget* _currentFocusWidget;
    };
}

#endif //GWUI_CONTROL_H
