//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_MESSAGEBOX_H
#define GWUI_MESSAGEBOX_H

#include <string>

#include "Dialog.h"

namespace GWUI
{
    class MessageBox
    {
    public:
        MessageBox(std::string msg, std::string title):
            _msgData(std::move(msg), std::move(title)){}

        MessageBox(MessageData data):_msgData(std::move(data)){}

        int Show();

    private:
        MessageData _msgData;
    };
}

#endif //GWUI_MESSAGEBOX_H
