//
// Created by fusionbolt on 2020/3/20.
//

#ifndef GWUI_METAINFO_H
#define GWUI_METAINFO_H

#include <string>

namespace GWUI
{
    bool IsLayout(const std::string& className);

    bool IsButton(const std::string& className);

    bool IsWidget(const std::string& className);

    bool IsSingleObject(const std::string& className);
}

#endif //GWUI_METAINFO_H
