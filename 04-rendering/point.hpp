#pragma once

#include <cstdint>

struct point
{
    uint16_t x;
    uint16_t y;

    point(uint16_t x_, uint16_t y_)
        : x(x_)
        , y(y_)
    {
    }

    point& operator+=(const point& rhs);
};

point operator+(const point& lhs, const point& rhs);

void swap(point& p1, point& p2);
