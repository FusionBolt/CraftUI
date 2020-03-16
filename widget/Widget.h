//
// Created by fusionbolt on 2020-01-26.
//

#ifndef GWUI_WIDGET_H
#define GWUI_WIDGET_H

#include <vector>
#include <queue>
#include "../units/Renderer.h"
#include "../core/Object.hpp"
#include "../core/Event.h"
#include "../units/Renderer.h"

namespace GWUI
{
    class Widget : public Object, public std::enable_shared_from_this<Widget>
    {
    public:
        // TODO:widget parent shared_ptr or weak_ptr
        // if weak_ptr , use weak_from_this instead of shared_from_this() in SetParent
        using Ptr = std::shared_ptr<Widget>;

        Widget() = default;

        virtual void Draw(Renderer &renderer);

        virtual void SetGeometry(Rect rect) noexcept;

        virtual Rect GetGeometry() const noexcept;

        void SetParent(const Ptr &parent);

        void RemoveChild(const Ptr &child);

        template<typename T = Widget>
        std::weak_ptr<T> WeakFromThis();

        // TODO:转换为weak_ptr？？避免返回智能指针产生各种奇怪的内存问题
        // 例如循环引用，不能正确的暗示释放对象
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

        template<typename T = Widget>
        std::shared_ptr<T> FindChild(const std::function<bool(Widget::Ptr)>& condition)
        {
            return std::dynamic_pointer_cast<T>(_findChild(condition));
        }

        void ShowAllChild() const;

        void SetTestMove(bool beMove) noexcept;

        void SetFocus(bool focus) noexcept;

    protected:
        friend class Control;

        Ptr _findChild(const std::function<bool(Widget::Ptr)>& checkFun);

        virtual void KeyPressEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void KeyReleaseEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void MousePressEvent(const MouseEvent &mouseEvent);

        virtual void MouseReleaseEvent(const MouseEvent &mouseEvent);

        virtual void MouseMotionEvent(const MouseEvent &mouseEvent);

        ~Widget() override = default;

        Rect _geometry = {0,0,0,0};

        std::weak_ptr<Widget> _parent;

        std::vector<Ptr> _childs;

        bool _focus = false;

        bool _hadClicked = false;

        bool _beTestMove = false;
    };
}

#endif //GWUI_WIDGET_H
