//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_WINDOW_H
#define GWUI_WINDOW_H

#include <string>

#include "../utils/Util.hpp"
#include "SDL.h"
#include "../units/Renderer.h"
#include "Widget.h"

namespace GWUI
{
    class Window : public Widget
    {
    public:
        explicit Window(const std::string& title = "GWUI", int width = 1024, int height = 768);

        void Show();

        Renderer GetRenderer() const;

        void SetWindowSize(int width, int height);

        void SetWindowTitle(const std::string& title);

        void SetWindowIcon(const std::string& path);

        void SetBackgroundColor(Color color);

        std::tuple<int, int> GetWindowSize();

    protected:
        friend class Renderer;

    private:
        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;

        std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> _icon;

        Renderer _renderer;

        Color _backgroundColor;
    };
}

#endif //GWUI_WINDOW_H
