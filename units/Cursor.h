//
// Created by fusionbolt on 2020/2/24.
//

#ifndef GWUI_CURSOR_H
#define GWUI_CURSOR_H

#include <iostream>

namespace Craft
{
    struct Cursor
    {
    public:
        Cursor();

        size_t Increase(int span = 1, size_t maxSize = 0) noexcept;

        size_t Decrease(int span = 1) noexcept;

        void SetValue(size_t value) noexcept;

        void Reset() noexcept;

        operator size_t() const noexcept;

    private:
        size_t _cursor;
    };
}

#endif //GWUI_CURSOR_H
