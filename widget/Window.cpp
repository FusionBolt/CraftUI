//
// Created by fusionbolt on 2020-01-24.
//

#include <iostream>
#include <SDL_image.h>

#include "Window.h"
#include "SDL_ttf.h"
#include "../core/Control.h"
#include "../Player.h"

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

    // Player player("/Users/fusionbolt/Movies/[BD适用]【银庭字幕组】[魔法少女小圆新篇 叛逆的物语][简繁外挂字幕][附考据]ver1.02/叛逆的物语.mkv", _renderer);
    // Player player("/Users/fusionbolt/Movies/27.mp4", _renderer);
    // Player player("/Users/fusionbolt/Music/suisei.mp4", _renderer);
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
