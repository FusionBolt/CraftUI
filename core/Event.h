//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_EVENT_H
#define GWUI_EVENT_H

#include <array>
#include <SDL.h>

#include "../common.hpp"

namespace GWUI
{
    using CrudeEvent = SDL_Event;

    class Event
    {
    public:
        Event() noexcept = default;

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
        explicit MouseEvent(CrudeEvent event) noexcept: _event(event){}

        [[nodiscard]] Point GetPosition() const noexcept {return {_event.motion.x, _event.motion.y};}

        [[nodiscard]] CrudeEvent GetEvent() const noexcept {return _event;}

    private:
        Point _position;
        CrudeEvent _event;
    };

    inline bool JudgeCoincide(Point mousePosition, SDL_Rect rect) noexcept
    {
        auto mouseX = mousePosition.x;
        auto mouseY = mousePosition.y;
        if (mouseX > rect.x && mouseX < rect.x + rect.w)
        {
            if (mouseY > rect.y && mouseY < rect.y + rect.h)
            {
                return true;
            }
        }
        return false;
    }
}

#endif //GWUI_EVENT_H
