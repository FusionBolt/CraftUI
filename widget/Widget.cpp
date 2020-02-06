//
// Created by fusionbolt on 2020-01-26.
//

#include "Widget.h"
#include "Button.h"

void GWUI::Widget::Draw(GWUI::Renderer renderer)
{
    for(const auto& child : _childs)
    {
        child->Draw(renderer);
    }
    Color c = {255, 0, 0};
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

    RendererRectangle(renderer.GetRenderer(), r1,c);
    RendererRectangle(renderer.GetRenderer(), r2,c);
    RendererRectangle(renderer.GetRenderer(), r3,c);
    RendererRectangle(renderer.GetRenderer(), r4,c);
    RendererRectangle(renderer.GetRenderer(), GetGeometry(), c, false);
}

void GWUI::Widget::SetGeometry(GWUI::Rect rect) noexcept
{
    _geometry = rect;
}

GWUI::Rect GWUI::Widget::GetGeometry() const noexcept
{
    return _geometry;
}

GWUI::Widget::Ptr GWUI::Widget::_findChild(std::function<bool(Widget::Ptr)> checkFun)
{
    for(auto& child : _childs)
    {
        //auto rect = child->GetGeometry();
        //std::cout << "objName " << child->GetObjectName() << std::endl;
        //std::cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << std::endl;
        if(std::invoke(checkFun, child))
        {
            return child;
        }
    }
    return nullptr;
}

void GWUI::Widget::MousePressEvent(const MouseEvent &mouseEvent)
{
    _canMove = true;
}

void GWUI::Widget::MouseReleaseEvent(const MouseEvent &mouseEvent)
{
    _canMove = false;
}

void GWUI::Widget::MouseMotionEvent(const MouseEvent &mouseEvent)
{
    if(_canMove)
    {
        auto position = mouseEvent.GetPosition();
        SetGeometry({position.x, position.y, _geometry.w, _geometry.h});
    }
}

void GWUI::Widget::SetParent(Widget::Ptr parent)
{
    if(parent!= nullptr)
    {
        _parent = parent;
        parent->_childs.push_back(std::dynamic_pointer_cast<Widget>(shared_from_this()));
    }
}

void GWUI::Widget::ShowAllChild() const
{
    std::cout << "childs start" << std::endl;
    for(const auto& child : _childs)
    {
        std::cout << child->GetObjectName() << std::endl;
    }
    std::cout << "childs end" << std::endl;
}
