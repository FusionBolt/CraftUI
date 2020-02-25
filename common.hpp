//
// Created by fusionbolt on 2020/2/25.
//

#ifndef GWUI_COMMON_HPP
#define GWUI_COMMON_HPP

#include <SDL.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

#define ERROR_INFO(errorInfo) std::cout << \
"error file:" << __FILE__ << std::endl << \
"Line:" << __LINE__ << std::endl <<\
 "function: "<< __FUNCTION__ << std::endl << \
errorInfo

namespace GWUI
{
    using Color = SDL_Color;

    using Rect = SDL_Rect;

    constexpr auto Black = Color{0,0,0, 255};
    constexpr auto White = Color{255,255,255, 255};

    struct Point
    {
        int x, y;
    };

    struct Line
    {
    public:
        Line(Point a, Point b){}

        Point a, b;
    };

    struct Circle
    {
    public:
        Circle(int nx, int ny, int nr):x(nx), y(ny), r(nr){}
        int x, y;
        int r;
        // TODO:uint??
    };

    inline std::string GetNowTimeStr()
    {
        auto timePoint = std::chrono::system_clock::now();
        std::time_t nowc = std::chrono::system_clock::to_time_t(timePoint);
        std::stringstream s;
        s << std::put_time(std::localtime(&nowc), "%F %T");
        return s.str();
    }
}
#endif //GWUI_COMMON_HPP
