//
// Created by fusionbolt on 2020-01-27.
//

#ifndef GWUI_OBJECT_HPP
#define GWUI_OBJECT_HPP

namespace GWUI
{
    class Object
    {
    public:
        void SetObjectName(std::string name)
        {
            _objName = std::move(name);
        }

        std::string GetObjectName() const
        {
            return _objName;
        }

    protected:
        std::string _objName = "defaultName";
    };
}


#endif //GWUI_OBJECT_HPP
