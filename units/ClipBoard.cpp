//
// Created by fusionbolt on 2020/3/16.
//

#include "ClipBoard.h"

void Craft::ClipBoard::SetText(const std::string &str)
{
    SDL_SetClipboardText(str.c_str());
}

std::string Craft::ClipBoard::GetText()
{
    return SDL_GetClipboardText();
}
