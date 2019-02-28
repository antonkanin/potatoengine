#pragma once

#include "vec3.hpp"

namespace ptm
{

struct matrix3x3
{
    vec3 row1;
    vec3 row2;
    vec3 row3;

    matrix3x3()
        : row1(1.f, 0.f, 0.f)
        , row2(0.f, 1.f, 0.f)
        , row3(0.f, 0.f, 1.f)
    {
    }
};

vec3 operator*(const matrix3x3& m, const vec3& v)
{
    return {m.row1 * v, m.row2 * v, m.row3 * v};
}

} // namespace ptm