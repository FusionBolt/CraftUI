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

namespace GWUI
{
    class Button : public Widget
    {
    public:
        explicit Button(Rect rect, const std::string& text = "Untitled");

        explicit Button(const std::string& text = "Untitled");

        void Draw(Renderer renderer) override;

        std::string GetText();

        void SetText(const std::string& text);

        void SetGeometry(Rect rect) noexcept override;

        void OnClicked(std::function<void()> f);

    protected:
        void MouseReleaseEvent(const MouseEvent &mouseEvent) override;

        void MousePressEvent(const MouseEvent &mouseEvent) override;

    private:
        std::function<void()> _onClicked;

        Text _text;

        Rectangle _rect;

        bool _click = false;
    };
}

#endif //GWUI_BUTTON_H
