//
// Created by fusionbolt on 2020-01-26.
//

#include "Widget.h"
#include "Button.h"

void GWUI::Widget::Draw(Renderer &renderer)
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

    renderer.RendererRectangle(r1,c);
    renderer.RendererRectangle(r2,c);
    renderer.RendererRectangle(r3,c);
    renderer.RendererRectangle(r4,c);
    renderer.RendererRectangle(GetGeometry(), c, false);
}

void GWUI::Widget::SetGeometry(GWUI::Rect rect) noexcept
{
    _geometry = rect;
}

GWUI::Rect GWUI::Widget::GetGeometry() const noexcept
{
    return _geometry;
}

GWUI::Widget::Ptr GWUI::Widget::_findChild(const std::function<bool(Widget::Ptr)>& checkFun)
{
    std::queue<std::shared_ptr<Widget>> q;
    std::vector<std::shared_ptr<Widget>> v;
    for(auto& child : _childs)
    {
        q.push(child);
    }
    while(!q.empty())
    {
        auto child = q.front();
        q.pop();
        if(std::invoke(checkFun, child))
        {
            //return child;
            v.push_back(child);
        }
        for(auto& c : child->_childs)
        {
            q.push(c);
        }
    }
    //return nullptr;
    return v.empty() ? nullptr : v[v.size()-1];
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
    if(_canMove && _beTestMove)
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
    for(const auto& child : _childs)
    {
        std::cout << child->GetObjectName() << std::endl;
    }
}

void GWUI::Widget::SetTestMove(bool beMove) noexcept
{
    _beTestMove = beMove;
}

void GWUI::Widget::SetFocus(bool focus) noexcept
{
    _focus = focus;
}
