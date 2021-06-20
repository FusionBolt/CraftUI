//
// Created by fusionbolt on 2020-02-07.
//

#ifndef GWUI_DIALOG_H
#define GWUI_DIALOG_H

#include <vector>
namespace Craft
{
    struct MessageData
    {
    public:
        MessageData(std::string title, std::string message, uint32_t flags = SDL_MESSAGEBOX_INFORMATION):
            _title(std::move(title)), _message(std::move(message)), _flags(flags){}

    protected:
        friend class Dialog;
        friend class MessageBox;

    private:
        uint32_t _flags;
        std::string _title, _message;
    };

    struct DialogButtonData
    {
    public:
        DialogButtonData(uint32_t flags, int buttonId, std::string text):
            _text(std::move(text)), _flags(flags), _buttonId(buttonId)
            {
            }

    protected:
        friend class Dialog;

    public:
        std::string _text;
        uint32_t _flags;
        int _buttonId;
    };

    class Dialog
    {
    public:
        Dialog(std::vector<DialogButtonData> buttonData, MessageData messageData);

        int Show();

    private:
        std::vector<DialogButtonData> _buttonData;
        MessageData _messageData;
    };
}



#endif //GWUI_DIALOG_H
