//
// Created by fusionbolt on 2020-01-24.
//

#include <iostream>

#include "Window.h"
#include "SDL_ttf.h"
#include "../core/Control.h"

GWUI::Window::Window(const std::string &title, int width, int height):
    _window(nullptr, SDL_DestroyWindow), Widget()
{
    _window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)); // | SDL_WINDOW_ALLOW_HIGHDPI
    if (_window == nullptr)
    {
        throw std::runtime_error("Create Window Failed");
    }
    _renderer.SetWindow(_window.get());
}

GWUI::Renderer GWUI::Window::GetRenderer() const
{
    return _renderer;
}

void GWUI::Window::Show() noexcept
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
        SDL_SetRenderDrawColor(_renderer.GetRenderer().get(), 121, 212, 251, 255);
        _renderer.RenderPresent();
        SDL_Delay(10);
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
