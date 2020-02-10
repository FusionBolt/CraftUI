//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_BUTTON_H
#define GWUI_BUTTON_H

#include <string>

#include "../units/Text.h"
#include "../units/Rectangle.hpp"
#include "../units/Renderer.hpp"
#include "Widget.h"
#include "AbstractButton.h"

namespace GWUI
{
    class Button : public AbstractButton
    {
    public:
        explicit Button(const std::string& text = "Untitled");

        void Draw(Renderer renderer) override;

        void SetGeometry(Rect rect) noexcept override;

    protected:
        void MouseReleaseEvent(const MouseEvent &mouseEvent) override;
    };
}

#endif //GWUI_BUTTON_H
