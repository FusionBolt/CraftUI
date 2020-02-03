//
// Created by fusionbolt on 2020-01-26.
//

#ifndef GWUI_WIDGET_H
#define GWUI_WIDGET_H

#include <vector>
#include <queue>
#include "../units/Renderer.hpp"
#include "../utils/Util.hpp"
#include "../core/Object.hpp"
#include "../core/Event.h"

namespace GWUI
{
    class Widget : public Object
    {
    public:
        using Ptr = Widget*;

        explicit Widget(Ptr parent);

        virtual void Draw(Renderer renderer);

        virtual void SetGeometry(Rect rect) noexcept;

        virtual Rect GetGeometry() const noexcept;

        template<typename T = Widget>
        T* FindChild(Point position)
        {
            return dynamic_cast<T*>(_findChild([=](Widget::Ptr widget){
                return JudgeCoincide(position, widget->GetGeometry());
            }));
        }

        template<typename T = Widget>
        T* FindChild(const std::string& name)
        {
            return dynamic_cast<T*>(_findChild([&](Widget::Ptr widget){
                return (name == widget->GetObjectName());
            }));
        }

    protected:
        friend class Control;

        Widget* _findChild(std::function<bool(Widget::Ptr)> checkFun);

        virtual void KeyPressEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void KeyReleaseEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void MousePressEvent(const MouseEvent &mouseEvent);

        virtual void MouseReleaseEvent(const MouseEvent &mouseEvent);

        virtual void MouseMotionEvent(const MouseEvent &mouseEvent);

        virtual ~Widget()
        {
            for(auto& child : _childs)
            {
                delete child;
            }
        }

        Rect _geometry;

        Ptr _parent;
        // TODO: 指针引用问题
        std::vector<Ptr> _childs;

        bool _focus = false;

        bool _canMove = false;
    };
}

#endif //GWUI_WIDGET_H
