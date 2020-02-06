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
    class Widget : public Object, public std::enable_shared_from_this<Widget>
    {
    public:
        using Ptr = std::shared_ptr<Widget>;

        Widget() = default;

        virtual void Draw(Renderer renderer);

        virtual void SetGeometry(Rect rect) noexcept;

        virtual Rect GetGeometry() const noexcept;

        void SetParent(Widget::Ptr parent);

        template<typename T = Widget>
        std::shared_ptr<T> FindChild(Point position)
        {
            return std::dynamic_pointer_cast<T>(_findChild([=](const Widget::Ptr& widget){
                return JudgeCoincide(position, widget->GetGeometry());
            }));
        }

        template<typename T = Widget>
        std::shared_ptr<T> FindChild(const std::string& name)
        {
            return std::dynamic_pointer_cast<T>(_findChild([&](const Widget::Ptr& widget){
                return (name == widget->GetObjectName());
            }));
        }

        void ShowAllChild() const;

    protected:
        friend class Control;

        Ptr _findChild(std::function<bool(Widget::Ptr)> checkFun);

        virtual void KeyPressEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void KeyReleaseEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void MousePressEvent(const MouseEvent &mouseEvent);

        virtual void MouseReleaseEvent(const MouseEvent &mouseEvent);

        virtual void MouseMotionEvent(const MouseEvent &mouseEvent);

        virtual ~Widget() = default;

        Rect _geometry = {0,0,0,0};

        std::weak_ptr<Widget> _parent;

        std::vector<Ptr> _childs;

        bool _focus = false;

        bool _canMove = false;
    };
}

#endif //GWUI_WIDGET_H
