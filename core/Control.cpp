//
// Created by fusionbolt on 2020-01-29.
//

#include "Control.h"
#include "../widget/Window.h"

void GWUI::Control::SetFocusWidget(Widget::Ptr widget)
{
    _currentFocusWidget = widget;
}

int GWUI::Control::EventDispatch(GWUI::CrudeEvent event, Widget::Ptr widget)
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
            auto e = MouseEvent(event);
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
        auto renderer = std::dynamic_pointer_cast<GWUI::Window>(widget)->GetRenderer().GetRenderer();
        std::cout << "print screen" << std::endl;
        SDL_Surface *sshot = SDL_CreateRGBSurface(0, 1024, 768, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
        SDL_SaveBMP(sshot, "screenshot.bmp");
        SDL_FreeSurface(sshot);
        //  about screenshot
        //  https://stackoverflow.com/questions/22315980/sdl2-c-taking-a-screenshot
    }
}
