#include "point.h"

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

point_array operator+(const point_array& lhs, const point& rhs)
{
    std::vector<point> result;

    for (const auto& p : lhs)
    {
        result.push_back(p + rhs);
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const point_array& points)
{
    for (const auto& p : points)
    {
        out << '(' << p.x << ',' << p.y << ") ";
    }
    return out;
}

point_array operator+(const point_array& lhs, const point_array& rhs)
{
    if (lhs.size() != rhs.size())
    {
        throw std::runtime_error("error: sizes do not match");
    }

    std::vector<point> result;

    for (size_t index = 0; index < lhs.size(); ++index)
    {
        result.push_back(lhs[index] + rhs[index]);
    }

    return result;
}

point& point::operator+=(const point& rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;

    return *this;
}
