#pragma once

#include <cstdint>
#include <ostream>
#include <vector>

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

///////////////////////////////////////////////////////////////////////////////
// point_array

typedef std::vector<point> point_array;

point_array operator+(const point_array& lhs, const point& rhs);

std::ostream& operator<<(std::ostream& out, const point_array& points);

point_array operator+(const point_array& lhs, const point_array& rhs);

// flips points array around the max Y value
point_array flip_y(const point_array& points);
