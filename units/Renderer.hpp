//
// Created by fusionbolt on 2020-01-26.
//

#ifndef GWUI_RENDERER_HPP
#define GWUI_RENDERER_HPP

#include <memory>
#include "SDL_render.h"

namespace GWUI
{
    class Renderer
    {
    public:
        Renderer():_renderer(nullptr, SDL_DestroyRenderer){}

        void SetWindow(SDL_Window* window)
        {
            _renderer.reset(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED),
                    SDL_DestroyRenderer);
        }

        void RenderClear()
        {
            SDL_RenderClear(_renderer.get());
        }

        void RenderPresent()
        {
            SDL_RenderPresent(_renderer.get());
        }

        std::shared_ptr<SDL_Renderer> GetRenderer() const
        {
            return _renderer;
        }

    private:
        std::shared_ptr<SDL_Renderer>  _renderer;
    };
}

#endif //GWUI_RENDERER_HPP
