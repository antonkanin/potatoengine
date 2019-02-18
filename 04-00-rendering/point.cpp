#include "point.hpp"
#include <algorithm>

void swap(point& p1, point& p2)
{
    auto temp = p1;
    p1        = p2;
    p2        = temp;
}

point operator+(const point& lhs, const point& rhs)
{
    return { static_cast<uint16_t>(lhs.x + rhs.x),
             static_cast<uint16_t>(lhs.y + rhs.y) };
}

point& point::operator+=(const point& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}
