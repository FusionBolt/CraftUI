//
// Created by fusionbolt on 2020/3/19.
//

#include "Object.h"
#include "MetaInfo.h"

void GWUI::Object::SetObjectName(std::string name)
{
    _objName = std::move(name);
}

std::string GWUI::Object::GetObjectName() const
{
    return _objName;
}

void GWUI::Object::SetParent(GWUI::Object::Ptr parent)
{
    if (parent!= nullptr)
    {
        auto oldParent = _parent.lock();
        if(oldParent != nullptr)
        {
            // TODO:考虑指针类型
            oldParent->RemoveChild(shared_from_this());
        }
        _parent = std::move(parent);
        parent->_childs.push_back(std::dynamic_pointer_cast<Object>(shared_from_this()));
    }
}

void GWUI::Object::RemoveChild(const GWUI::Object::Ptr &child)
{
    // TODO:C++20 erase_if
    auto iter = std::find(_childs.begin(), _childs.end(), child);
    if(iter != _childs.end())
    {
        _childs.erase(iter);
    }
}

void GWUI::Object::ShowAllChild() const
{
//    for(const auto& child : _childs)
//    {
//        std::cout << child->GetObjectName() << std::endl;
//    }
    auto thisPtr = std::const_pointer_cast<Object>(shared_from_this());
    thisPtr->AllChildDo([](auto &&o)
                        { std::cout << o->GetObjectName() << std::endl; }, thisPtr);
}

GWUI::Object::Ptr GWUI::Object::_findChild(const std::function<bool(Ptr)>& checkFun)
{
    std::queue<Object::Ptr> q;
    std::vector<Object::Ptr> v;
    for(auto& child : _childs)
    {
        q.push(child);
    }
    while(!q.empty())
    {
        auto child = q.front();
        q.pop();
        if (std::invoke(checkFun, child))
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

void GWUI::Object::SetClassName(std::string name)
{
    _className = std::move(name);
}

std::string GWUI::Object::GetClassName() const
{
    return _className;
}

void GWUI::Object::AllChildDo(const std::function<void(Ptr)> &callable, GWUI::Object::Ptr &root)
{
    for(auto& child : root->_childs)
    {
        if(IsSingleObject(child->GetClassName()))
        {
            callable(child);
        }
        else
        {
            AllChildDo(callable, child);
        }
    }
}

