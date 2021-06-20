//
// Created by fusionbolt on 2020-01-26.
//

#include "Widget.h"
#include "Button.h"
#include "../core/MetaInfo.h"

void Craft::Widget::Draw(Renderer &renderer)
{
    auto thisPtr = shared_from_this();
    AllChildDo([&](auto &&widget)
               {
                   auto className = widget->GetClassName();
                   if (IsWidget(className))
                   {
                       std::dynamic_pointer_cast<Widget>(widget)->Draw(renderer);
                   }
               }, thisPtr);

//    for(const auto& child : _childs)
//    {
//        auto className = child->GetClassName();
//        if(IsWidget(className))
//        {
//            std::dynamic_pointer_cast<Widget>(child)->Draw(renderer);
//        }
//        else
//        {
//
//        }
//    }

    Color c = {255, 0, 0, 255};
    Rect r1 = GetGeometry();
    r1.x = r1.x - 3;
    r1.y = r1.y - 3;
    r1.w = 6;
    r1.h = 6;
    auto r2 = r1;
    r2.y = r1.y + GetGeometry().h;
    auto r3 = r1;
    r3.x = r1.x + GetGeometry().w;
    auto r4 = r1;
    r4.x = r1.x + GetGeometry().w;
    r4.y = r1.y + GetGeometry().h;

    renderer.RenderRectangle(r1, c);
    renderer.RenderRectangle(r2, c);
    renderer.RenderRectangle(r3, c);
    renderer.RenderRectangle(r4, c);
    // renderer.RenderRectangle(GetGeometry(), c);
}

void Craft::Widget::SetGeometry(Craft::Rect rect) noexcept
{
    _geometry = rect;
}

Craft::Rect Craft::Widget::GetGeometry() const noexcept
{
    return _geometry;
}

void Craft::Widget::MousePressEvent(const MouseEvent &mouseEvent)
{
    _hadClicked = true;
}

void Craft::Widget::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    _hadClicked = false;
}

void Craft::Widget::MouseMotionEvent(const MouseEvent &mouseEvent)
{
    if (_hadClicked && _beTestMove)
    {
        auto position = mouseEvent.GetPosition();
        SetGeometry({position.x, position.y, _geometry.w, _geometry.h});
    }
}

void Craft::Widget::SetTestMove(bool beMove) noexcept
{
    _beTestMove = beMove;
}

void Craft::Widget::SetFocus(bool focus) noexcept
{
    _focus = focus;
}

template<typename T>
std::weak_ptr<T> Craft::Widget::WeakFromThis()
{
    return std::dynamic_pointer_cast<T>(shared_from_this());
}