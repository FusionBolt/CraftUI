//
// Created by fusionbolt on 2020-01-27.
//

#ifndef GWUI_OBJECT_H
#define GWUI_OBJECT_H

#include <vector>
#include <queue>
#include <string>
#include "../common.hpp"

namespace Craft
{
    // TODO:widget parent shared_ptr or weak_ptr
    // if weak_ptr , use weak_from_this instead of shared_from_this() in SetParent
    // TODO:转换为weak_ptr？？避免返回智能指针产生各种奇怪的内存问题
    // 例如循环引用，不能正确的暗示释放对象
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        using Ptr = std::shared_ptr<Object>;

        void SetObjectName(std::string name);

        [[nodiscard]] std::string GetObjectName() const;

        virtual void SetParent(Ptr parent);

        void RemoveChild(const Ptr& child);

        void SetClassName(std::string name);

        [[nodiscard]] std::string GetClassName() const;

        template<typename T = Object>
        std::shared_ptr<T> FindChild(const std::string& name)
        {
            return std::dynamic_pointer_cast<T>(_findChild([&](const Ptr& widget){
                return (name == widget->GetObjectName());
            }));
        }

        template<typename T = Object>
        std::shared_ptr<T> FindChild(const std::function<bool(Ptr)>& condition)
        {
            return std::dynamic_pointer_cast<T>(_findChild(condition));
        }

        void ShowAllChild() const;

        // TODO：下一次修改
        //TODO:设计有问题
        // 比如说显示全部子对象，非single会被无视掉
        // 还要用一个root参数
        // 这个引用一定需要么，牵扯到指针转换是临时对象
        // 管理对象树的问题
        void AllChildDo(const std::function<void(Ptr)>& callable, Object::Ptr& root);

    protected:
        Ptr _findChild(const std::function<bool(Ptr)>& checkFun);

        std::string _objName = "defaultName";

        virtual ~Object(){}

        std::vector<Ptr> _childs;

        std::weak_ptr<Object> _parent;

        std::string _className = "";
    };
}


#endif //GWUI_OBJECT_H
