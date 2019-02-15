#pragma once

#include "color.hpp"
#include "math_utils.hpp"

struct vertex
{
    float x;
    float y;
    color c;
};

typedef std::vector<vertex> vertex_array;

inline vertex lerp(const vertex& v1, const vertex& v2, const float t)
{
    return { lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t), lerp(v1.c, v2.c, t) };
}

inline void swap(vertex& vertex1, vertex& vertex2)
{
    std::swap(vertex1.x, vertex2.x);
    std::swap(vertex1.y, vertex2.y);
    std::swap(vertex1.c, vertex2.c);
}

