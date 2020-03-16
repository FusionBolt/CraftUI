//
// Created by fusionbolt on 2020/3/16.
//

#ifndef GWUI_MOUSECURSOR_H
#define GWUI_MOUSECURSOR_H

#include <memory>
#include <SDL.h>

namespace GWUI
{
class MouseCursor
{
public:
    static void SetCursor(SDL_SystemCursor type);

private:
    static std::shared_ptr<SDL_Cursor> cursor;
};
}

#endif //GWUI_MOUSECURSOR_H
