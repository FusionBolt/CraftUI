//
// Created by fusionbolt on 2020-01-29.
//

#include "Control.h"
#include "../widget/Window.h"

int GWUI::Control::EventDispatch(GWUI::CrudeEvent &event, Widget::Ptr widget)
{
    if(event.type == SDL_QUIT)
    {
        return 0;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        Point mousePosition{event.motion.x, event.motion.y};
        std::cout << "mouse button down:" << mousePosition.x << "," << mousePosition.y << std::endl;
        auto targetWidget = widget->FindChildAt(mousePosition);
        if(targetWidget != nullptr)
        {
            SetWidgetFocus(targetWidget);
            std::cout << "focus on:" << _currentFocusWidget->GetObjectName() << std::endl;
            auto e = MouseEvent(event);
            _currentFocusWidget->MousePressEvent(e);
        }
        else
        {
            std::cout << "not found" << std::endl;
        }
    }
    if(event.type == SDL_MOUSEBUTTONUP)
    {
        Point mousePosition{event.motion.x, event.motion.y};
        auto e = MouseEvent(event);
        if(_currentFocusWidget != nullptr)
        {
            _currentFocusWidget->MouseReleaseEvent(e);
        }
    }
    if(event.type == SDL_MOUSEMOTION)
    {
        Point mousePosition{event.motion.x, event.motion.y};
        auto e = MouseEvent(event);

        // TODO:about childDo error
        auto obj = std::dynamic_pointer_cast<Object>(widget);
        widget->AllChildDo([=](auto&& w){
            std::dynamic_pointer_cast<Widget>(w)->MouseMotionEvent(e);
        }, obj);

    }
    if(event.type == SDL_KEYDOWN || event.type == SDL_TEXTINPUT || event.type == SDL_TEXTEDITING)
    {
        auto e = KeyBoardEvent(event);
        if(_currentFocusWidget != nullptr)
        {
            _currentFocusWidget->KeyPressEvent(e);
        }
    }
    if(event.key.keysym.sym == SDLK_PRINTSCREEN)
    {
        // TODO: 不是window?
        std::dynamic_pointer_cast<GWUI::Window>(widget)->ScreenShot();
    }
    return 0;
}

void GWUI::Control::SetWidgetFocus(Widget::Ptr nextFocusWidget)
{
    if(_currentFocusWidget == nextFocusWidget)
    {
        return;
    }
    if(_currentFocusWidget != nullptr)
    {
        _currentFocusWidget->SetFocus(false);
    }
    nextFocusWidget->SetFocus(true);
    _currentFocusWidget = std::move(nextFocusWidget);
}
