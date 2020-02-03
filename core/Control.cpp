//
// Created by fusionbolt on 2020-01-29.
//

#include "Control.h"

void GWUI::Control::SetFocusWidget(Widget* widget)
{
    _currentFocusWidget = widget;
}

int GWUI::Control::EventDispatch(GWUI::CrudeEvent event, Widget* widget)
{
    if(event.type == SDL_QUIT)
    {
        return 0;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        Point mousePosition{event.motion.x, event.motion.y};
        std::cout << "mouse button down:" << mousePosition.x << "," << mousePosition.y << std::endl;
        auto targetWidget = widget->FindChild(mousePosition);
        if(targetWidget != nullptr)
        {
            targetWidget->_focus = true;
            _currentFocusWidget = targetWidget;
            std::cout << "focus on:" << _currentFocusWidget->GetObjectName() << std::endl;
            auto e = MouseEvent(mousePosition);
            targetWidget->MousePressEvent(e);
        }
        else
        {
            std::cout << "not found" << std::endl;
        }
    }
    if(event.type == SDL_MOUSEBUTTONUP)
    {
        Point mousePosition{event.motion.x, event.motion.y};
        auto e = MouseEvent(mousePosition);
        if(_currentFocusWidget != nullptr)
        {
            _currentFocusWidget->MouseReleaseEvent(e);
        }
    }
    if(event.type == SDL_MOUSEMOTION)
    {
        Point mousePosition{event.motion.x, event.motion.y};
        auto e = MouseEvent(mousePosition);
        for(auto& child : widget->_childs)
        {
            child->MouseMotionEvent(e);
        }
//        auto child = widget->FindChild(mousePosition);
//        if(child != nullptr)
//        {
//            child->MouseMotionEvent(&e);
//        }
    }
    if(event.type == SDL_KEYDOWN)
    {
        auto e = KeyBoardEvent(event);
        if(_currentFocusWidget != nullptr)
        {
            _currentFocusWidget->KeyPressEvent(e);
        }
    }
}
