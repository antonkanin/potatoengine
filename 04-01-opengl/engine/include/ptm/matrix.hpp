#pragma once

#include "vec3.hpp"
#include "vec4.hpp"

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

struct matrix4x4
{
    vec4 row1;
    vec4 row2;
    vec4 row3;
    vec4 row4;

    matrix4x4()
        : row1(1.f, 0.f, 0.f, 0.f)
        , row2(0.f, 1.f, 0.f, 0.f)
        , row3(0.f, 0.f, 1.f, 0.f)
        , row4(0.f, 0.f, 0.f, 1.f)

    {
    }

    matrix4x4(const matrix3x3& matrix)
        : row1(matrix.row1, 0)
        , row2(matrix.row2, 0)
        , row3(matrix.row3, 0)
        , row4(0.f, 0.f, 0.f, 1.f)
    {
    }
};

inline vec3 operator*(const matrix3x3& m, const vec3& v)
{
    return { m.row1 * v, m.row2 * v, m.row3 * v };
}

} // namespace ptm