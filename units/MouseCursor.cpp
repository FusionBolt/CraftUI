//
// Created by fusionbolt on 2020/3/16.
//

#include "MouseCursor.h"

std::shared_ptr<SDL_Cursor> Craft::MouseCursor::cursor(
        SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW),
        SDL_FreeCursor);

void Craft::MouseCursor::SetCursor(SDL_SystemCursor type)
{
    cursor.reset(SDL_CreateSystemCursor(type),
            SDL_FreeCursor);
    SDL_SetCursor(cursor.get());
}