//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_UTIL_HPP
#define GWUI_UTIL_HPP

#include <iostream>

#define ERROR_INFO(errorInfo) std::cout << \
"error file:" << __FILE__ << std::endl << \
"Line:" << __LINE__ << std::endl <<\
 "function: "<< __FUNCTION__ << std::endl << \
errorInfo

namespace GWUI
{
    struct Point
    {
        int x, y;
    };
}


#endif //GWUI_UTIL_HPP
