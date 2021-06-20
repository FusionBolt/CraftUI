//
// Created by fusionbolt on 2020-02-07.
//

#include <SDL_messagebox.h>
#include <SDL_log.h>
#include <iostream>

#include "Dialog.h"

int Craft::Dialog::Show()
{
    std::vector<SDL_MessageBoxButtonData> buttons;
    for(auto& v : _buttonData)
    {
        buttons.push_back({v._flags, v._buttonId, v._text.c_str()});
    }

    SDL_MessageBoxData messageboxdata = {
            _messageData._flags, /* .flags */
            nullptr, /* .window */
            _messageData._title.c_str(), /* .title */
            _messageData._message.c_str(), /* .message */
            static_cast<int>(_buttonData.size()), /* .numbuttons */
            buttons.data(), /* .buttons */
            nullptr /* .colorScheme */
    };

    int buttonId;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonId) < 0)
    {
        SDL_Log("error displaying message box");
        return 1;
    }
    if (buttonId == -1)
    {
        std::cout << "no selection" << buttonId << std::endl;
        SDL_Log("no selection");
    }
    else
    {
        SDL_Log("selection was %s", buttons[buttonId].text);
    }
    std::cout << "push button id:" << buttonId << std::endl;
    return 0;
}

Craft::Dialog::Dialog(std::vector<DialogButtonData> buttonData, Craft::MessageData messageData):
    _buttonData(std::move(buttonData)), _messageData(std::move(messageData))
{

}
