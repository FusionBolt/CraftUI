//
// Created by fusionbolt on 2020/2/24.
//

#include "Cursor.h"

GWUI::Cursor::Cursor():_cursor(0)
{

}

size_t GWUI::Cursor::Increase(int span, size_t maxSize) noexcept
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

size_t GWUI::Cursor::Decrease(int span) noexcept
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

void GWUI::Cursor::SetValue(size_t value) noexcept
{
    _cursor = value;
}

void GWUI::Cursor::Reset() noexcept
{
    std::cout << "cursor reset 0" << std::endl;
    _cursor = 0;
}

GWUI::Cursor::operator size_t() const noexcept
{
    return _cursor;
}
