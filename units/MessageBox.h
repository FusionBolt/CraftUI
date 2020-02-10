//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_MESSAGEBOX_H
#define GWUI_MESSAGEBOX_H

#include <string>

namespace GWUI
{
    class MessageBox
    {
    public:
        MessageBox(std::string msg, std::string title):
            _msg(std::move(msg)),_title(std::move(title)){}

        int Show();

    private:
        std::string _msg, _title;
    };
}

#endif //GWUI_MESSAGEBOX_H
