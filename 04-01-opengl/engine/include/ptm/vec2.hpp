#pragma once

#include <ostream>

namespace ptm
{

struct vec2
{
    float x;
    float y;

    constexpr vec2(float x, float y)
        : x(x)
        , y(y)
    {
    }
};

struct vec2i
{
    int x;
    int y;

    vec2i(int x, int y)
        : x(x)
        , y(y)
    {
    }
};

inline std::ostream& operator<<(std::ostream& out, const vec2& value)
{
    out << value.x << ' ' << value.y;
    return out;
}

} // namespace ptm
