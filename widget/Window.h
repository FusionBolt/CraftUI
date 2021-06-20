//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_WINDOW_H
#define GWUI_WINDOW_H

#include <string>
#include <SDL.h>

#include "../units/Renderer.h"
#include "Widget.h"

namespace Craft
{
    class Window : public Widget
    {
    public:
        explicit Window(const std::string& title = "Craft", int width = 1024, int height = 768);

        void Show();

        void SetWindowSize(int width, int height);

        void SetWindowTitle(const std::string& title);

        void SetWindowIcon(const std::string& path);

        void SetBackgroundColor(Color color);

        void SetWindowOpacity(float opacity);

        void SetWindowBorder(bool show);

        void SetWindowFullScreen(uint32_t flags);

        std::tuple<int, int> GetWindowSize();

        void ScreenShot() const;

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
