//
// Created by fusionbolt on 2020-01-24.
//

#include <iostream>
#include <SDL_image.h>

#include "Window.h"
#include "../core/Control.h"
#include "../Player.h"
#include "../units/Image.h"

GWUI::Window::Window(const std::string &title, int width, int height):Widget(),
    _window(nullptr, SDL_DestroyWindow), _icon(nullptr, SDL_FreeSurface),
    _backgroundColor({121, 212, 251, 255})
{
    _window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)); // | SDL_WINDOW_ALLOW_HIGHDPI
    if (_window == nullptr)
    {
        throw std::runtime_error("Create Window Failed");
    }
    _renderer.SetWindow(this);

    SetWindowIcon("/Users/fusionbolt/Pictures/AlfredIcon/pmwk.png");
}

void GWUI::Window::Show()
{
    CrudeEvent e;
    auto c = std::make_shared<Control>();

    // TODO: 当焦点在可编辑组件当时候开启 性能差距
    SDL_StartTextInput();

    while (true)
    {
        if (SDL_PollEvent(&e))
        {
            if (SDL_QUIT == e.type)
            {
                std::cout << "SDL quit" << std::endl;
                break;
            }
            c->EventDispatch(e, shared_from_this());
        }
        _renderer.RenderClear();
        Draw(_renderer);
        _renderer.RenderCircle({600, 600, 100}, GWUI::Black);
        _renderer.RenderFillCircle({750, 300, 100}, {255,140,0, 255});
        _renderer.SetRenderDrawColor(_backgroundColor);
        _renderer.RenderPresent();
        SDL_Delay(7);
    }
}

void GWUI::Window::SetWindowSize(int width, int height)
{
    SDL_SetWindowSize(_window.get(), width, height);
}

void GWUI::Window::SetWindowTitle(const std::string& title)
{
    SDL_SetWindowTitle(_window.get(), title.c_str());
}

void GWUI::Window::SetWindowIcon(const std::string& path)
{
    SDL_SetWindowIcon(_window.get(), IMG_Load(path.c_str()));
}

void GWUI::Window::SetBackgroundColor(Color color)
{
    _backgroundColor = color;
}

std::tuple<int, int> GWUI::Window::GetWindowSize()
{
    int w, h;
    SDL_GetWindowSize(_window.get(), &w, &h);
    return {w, h};
}

void GWUI::Window::ScreenShot() const
{
    _renderer.ScreenShot();
}

void GWUI::Window::SetWindowOpacity(float opacity)
{
    if(opacity >= 0 && opacity <= 1)
    {
        SDL_SetWindowOpacity(_window.get(), opacity);
    }
}

void GWUI::Window::SetWindowBorder(bool show)
{
    SDL_bool b;
    if (show)
    {
        b = SDL_TRUE;
    }
    else
    {
        b = SDL_FALSE;
    }
    SDL_SetWindowBordered(_window.get(), b);
}

void GWUI::Window::SetWindowFullScreen(uint32_t flags)
{
    SDL_SetWindowFullscreen(_window.get(), flags);
}
