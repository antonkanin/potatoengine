#pragma once

#include "vec3.hpp"

namespace ptm
{

struct vec4
{
    float x;
    float y;
    float z;
    float w;

    vec4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    vec4(const vec3& vec3_, float w)
        : x(vec3_.x)
        , y(vec3_.y)
        , z(vec3_.z)
        , w(w)
    {
    }
};

} // namespace ptm