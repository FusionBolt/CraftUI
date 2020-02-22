//
// Created by fusionbolt on 2020-02-07.
//

#include <SDL_messagebox.h>
#include <SDL_log.h>

#include "MessageBox.h"

int GWUI::MessageBox::Show()
{
    SDL_ShowSimpleMessageBox(_msgData._flags,
                             _msgData._title.c_str(),
                             _msgData._message.c_str(),
                             nullptr);
}