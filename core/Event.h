//
// Created by fusionbolt on 2020-01-29.
//

#ifndef GWUI_EVENT_H
#define GWUI_EVENT_H

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
        explicit KeyBoardEvent(CrudeEvent e):event(e){}

        CrudeEvent event;
    };

    class MouseEvent : public Event
    {
    public:
        explicit MouseEvent(Point position) : _position(position){}

        Point GetPosition() const {return _position;}

    private:
        Point _position;
    };
}

#endif //GWUI_EVENT_H
