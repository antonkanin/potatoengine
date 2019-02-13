#include "point_array.hpp"

#include "point.hpp"
#include <algorithm>
#include <vector>

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

point_array flip_y(const point_array& points)
{
    // fix max y
    auto max = std::max_element(
        std::begin(points), std::end(points),
        [](const point& p1, const point& p2) { return p1.x < p2.x; });

    point_array result;

    for (auto& p : points)
    {
        result.push_back(
            { static_cast<uint16_t>(p.x + 2 * (max->x - p.x)), p.y });
    }

    return result;
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
