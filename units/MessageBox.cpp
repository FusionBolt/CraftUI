//
// Created by fusionbolt on 2020-02-07.
//

#include <SDL_messagebox.h>
#include <SDL_log.h>

#include "MessageBox.h"

int GWUI::MessageBox::Show()
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             _title.c_str(),
                             _msg.c_str(),
                             NULL);
}
