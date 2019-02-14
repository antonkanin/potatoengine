#pragma once

#include "color.hpp"
#include "math_utils.hpp"

struct vertex
{
    float x;
    float y;
    color c;
};

vertex lerp(const vertex& v1, const vertex& v2, const float t)
{
    return { lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t),
             lerp(v1.c, v2.c, t) };
}
