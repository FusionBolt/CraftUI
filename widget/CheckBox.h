//
// Created by fusionbolt on 2020-01-30.
//

#ifndef GWUI_CHECKBOX_H
#define GWUI_CHECKBOX_H

#include "AbstractButton.h"
#include "../units/Rectangle.hpp"

namespace GWUI
{
    class CheckBox : public AbstractButton
    {
    public:
        explicit CheckBox(const std::string& text = "CheckBox");

        void Draw(Renderer &renderer) override;

        void SetGeometry(Rect rect) noexcept override;
    };
}

#endif //GWUI_CHECKBOX_H
