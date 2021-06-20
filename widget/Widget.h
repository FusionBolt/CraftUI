//
// Created by fusionbolt on 2020-01-26.
//

#ifndef GWUI_WIDGET_H
#define GWUI_WIDGET_H

#include <vector>
#include <queue>
#include "../units/Renderer.h"
#include "../core/Object.h"
#include "../core/Event.h"
#include "../units/Renderer.h"
#include "../core/MetaInfo.h"

namespace GWUI
{
    class Widget : public Object
    {
    public:

        using Ptr = std::shared_ptr<Widget>;

        Widget() = default;

        virtual void Draw(Renderer &renderer);

        virtual void SetGeometry(Rect rect) noexcept;

        virtual Rect GetGeometry() const noexcept;

        template<typename T = Widget>
        std::weak_ptr<T> WeakFromThis();

        template<typename T = Widget>
        std::shared_ptr<T> FindChildAt(Point position)
        {
            // TODO:fix
            return std::dynamic_pointer_cast<T>(_findChild([=](const Object::Ptr& widget){
                if(!IsWidget(widget->GetClassName()))
                {
                    return false;
                }
                return JudgeCoincide(position, std::dynamic_pointer_cast<Widget>(widget)->GetGeometry());
            }));
        }

        void SetTestMove(bool beMove) noexcept;

        void SetFocus(bool focus) noexcept;

    protected:
        friend class Control;

        virtual void KeyPressEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void KeyReleaseEvent(const KeyBoardEvent &keyBoardEvent){}

        virtual void MousePressEvent(const MouseEvent &mouseEvent);

        virtual void MouseReleaseEvent(const MouseEvent &mouseEvent);

        virtual void MouseMotionEvent(const MouseEvent &mouseEvent);

        ~Widget() override = default;

        Rect _geometry = {0,0,0,0};

        bool _focus = false;

        bool _hadClicked = false;

        bool _beTestMove = false;
    };
}

#endif //GWUI_WIDGET_H
