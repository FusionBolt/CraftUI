//
// Created by fusionbolt on 2020-01-26.
//

#ifndef GWUI_SYSTEM_HPP
#define GWUI_SYSTEM_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../utils/Util.hpp"
#include "SDL.h"
#include "SDL_image.h"

namespace GWUI
{
    class System
    {
    public:
        System()
        {
            //initialize all SDL subsystems
            if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
            {
                ERROR_INFO("SDL Init Failed");
                throw std::runtime_error(SDL_GetError());
            }
            if (TTF_Init() == -1)
            {
                ERROR_INFO("TTF Init Failed");
                throw std::runtime_error(SDL_GetError());
            }
            if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
            {
                ERROR_INFO("IMG Init Failed");
                throw std::runtime_error(SDL_GetError());
            }
            if (Mix_Init(MIX_INIT_MP3) == -1)
            {
                ERROR_INFO("Mp3 Init Failed");
                throw std::runtime_error(SDL_GetError());
            }
            if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
            {
                ERROR_INFO("Audio Init Failed");
                throw std::runtime_error(SDL_GetError());
            }
        }

        ~System() noexcept
        {
            TTF_Quit();
            SDL_Quit();
            Mix_Quit();
            Mix_CloseAudio();
        }
    };
}


#endif //GWUI_SYSTEM_HPP
