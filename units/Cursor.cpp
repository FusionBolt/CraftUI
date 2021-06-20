//
// Created by fusionbolt on 2020/2/24.
//

#include "Cursor.h"

Craft::Cursor::Cursor(): _cursor(0)
{

}

size_t Craft::Cursor::Increase(int span, size_t maxSize) noexcept
{
    // guarantee _cursor + span > 0
    if (maxSize == 0 || ((_cursor + span) <= maxSize))
    {
        if(span < 0 && (_cursor < std::abs(span)))
        {

        }
        else
        {
            _cursor += span;
        }
    }
    else
    {
        _cursor = maxSize;
    }
    std::cout << "_cursor + " << span << " is" << _cursor << std::endl;
    return _cursor;
}

size_t Craft::Cursor::Decrease(int span) noexcept
{
    if (_cursor >= span)
    {
        _cursor -= span;
    }
    else
    {
        _cursor = 0;
    }
    std::cout << "_cursor - " << span << " is" << _cursor << std::endl;;
    return _cursor;
}

void Craft::Cursor::SetValue(size_t value) noexcept
{
    _cursor = value;
}

void Craft::Cursor::Reset() noexcept
{
    std::cout << "cursor reset 0" << std::endl;
    _cursor = 0;
}

Craft::Cursor::operator size_t() const noexcept
{
    return _cursor;
}
