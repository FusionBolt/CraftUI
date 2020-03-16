//
// Created by fusionbolt on 2020/3/16.
//

#include "ClipBoard.h"

void GWUI::ClipBoard::SetText(const std::string &str)
{
    SDL_SetClipboardText(str.c_str());
}

std::string GWUI::ClipBoard::GetText()
{
    return SDL_GetClipboardText();
}
