//
// Created by fusionbolt on 2020/2/25.
//

#include "System.h"

GWUI::System::System()
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

GWUI::System::~System()
{
    TTF_Quit();
    SDL_Quit();
    Mix_Quit();
    Mix_CloseAudio();
}

