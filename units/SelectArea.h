//
// Created by fusionbolt on 2020/2/24.
//

#ifndef GWUI_SELECTAREA_H
#define GWUI_SELECTAREA_H


#include "Renderer.h"

namespace Craft
{
    class SelectArea
    {
    public:
        void SetFirstClickPosition(Point position) noexcept;

        void UpdateSelectArea(Point position);

    private:
        Rect _selectArea;

        Point _firstClickPosition;
    };
}


#endif //GWUI_SELECTAREA_H
