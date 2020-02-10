//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_EVENT_H
#define GWUI_EVENT_H

#include <array>

#include "../utils/Util.hpp"

namespace GWUI
{
    class Event
    {
    public:
        Event() = default;

    private:
        int _eventType;
    };

    class KeyBoardEvent : public Event
    {
    public:
        explicit KeyBoardEvent(CrudeEvent e):event(e){f();}

        void f()
        {
            auto key = event.key.keysym.sym;
            auto mod = event.key.keysym.mod;
            char inputChar = ' ';
            if(key >= SDLK_0 && key <= SDLK_9)
            {
                std::array<char, 10> keyMap = {')', '!','@','#','$','%','^','&','*','('};
                if(mod & KMOD_SHIFT)
                {
                    inputChar = keyMap[key-SDLK_0];
                    std::cout << "inputChar is" << inputChar << std::endl;
                }
                std::cout << "push key 1-9" << std::endl;
            }
            if(key == SDLK_SPACE)
            {
                inputChar = ' ';
            }
        }

        CrudeEvent event;
    };

    class MouseEvent : public Event
    {
    public:
        explicit MouseEvent(CrudeEvent event) : _event(event){}

        Point GetPosition() const {return {_event.motion.x, _event.motion.y};}

        CrudeEvent GetEvent() const {return _event;}

    private:
        Point _position;
        CrudeEvent _event;
    };
}

#endif //GWUI_EVENT_H
