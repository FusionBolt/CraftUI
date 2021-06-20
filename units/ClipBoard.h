//
// Created by fusionbolt on 2020/3/16.
//

#ifndef GWUI_CLIPBOARD_H
#define GWUI_CLIPBOARD_H

#include <string>
#include <SDL.h>

namespace Craft
{
    class ClipBoard
    {
    public:
        static void SetText(const std::string &str);

        static std::string GetText();
    };
}


#endif //GWUI_CLIPBOARD_H
