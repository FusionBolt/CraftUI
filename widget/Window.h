//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_WINDOW_H
#define GWUI_WINDOW_H

#include <string>

#include "../utils/Util.hpp"
#include "SDL.h"
#include "../units/Renderer.hpp"
#include "Widget.h"

namespace GWUI
{
    class Window : public Widget
    {
    public:
        explicit Window(Widget::Ptr parent = nullptr, const std::string& title= "GWUI", int width = 1024, int height = 768);

        void Show() noexcept;

    private:
        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;

        Renderer _renderer;
    };
}

#endif //GWUI_WINDOW_H
