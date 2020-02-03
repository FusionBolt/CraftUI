//
// Created by fusionbolt on 2020-01-24.
//

#include <iostream>

#include "Window.h"
#include "SDL_ttf.h"
#include "../core/Control.h"

GWUI::Window::Window(Widget::Ptr parent, const std::string &title, int width, int height):
    _window(nullptr, SDL_DestroyWindow), Widget(parent)
{
    _window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)); // | SDL_WINDOW_ALLOW_HIGHDPI
    if (_window == nullptr)
    {
        throw std::runtime_error("Create Window Failed");
    }
    _renderer.SetWindow(_window.get());
}

void GWUI::Window::Show() noexcept
{
    CrudeEvent e;
    auto* c = new Control();
    while (true)
    {
        if (SDL_PollEvent(&e))
        {
            if (SDL_QUIT == e.type)
            {
                std::cout << "SDL quit" << std::endl;
                break;
            }
            c->EventDispatch(e, this);
            //HandleEvent(e);
        }
//        if(SDL_GetModState() == KMOD_LSHIFT)
//        {
//            std::cout << "LSHIFT" << std::endl;
//        }
//        else if(SDL_GetModState() == KMOD_CAPS)
//        {
//            std::cout << "CAPS" << std::endl;
//        }
        _renderer.RenderClear();
        Draw(_renderer);
        _renderer.RenderPresent();
        SDL_Delay(10);
    }
}
