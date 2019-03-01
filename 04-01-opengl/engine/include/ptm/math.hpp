#include <cmath>

#include <cmath>

#include <cmath>

#pragma once

#include "matrix.hpp"
#include "vec3.hpp"
#include <cmath>

namespace ptm
{

inline vec3 cross(const vec3& lhs, const vec3& rhs)
{
    // clang-format off
    return { lhs.y * rhs.z - lhs.z * rhs.y,
             lhs.z * rhs.x - lhs.x * rhs.z,
             lhs.x * rhs.y - lhs.y * rhs.x };
    // clang-format on
}

inline float dot(const vec3& lhs, const vec3& rhs)
{
    return lhs * rhs;
}

inline float length(const vec3& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec3 normalize(const vec3& v)
{
    const auto l = length(v);
    return { v.x / l, v.y / l, v.z / l };
}

inline vec3 projection(const vec3& from, const vec3& to)
{
    // https://en.wikipedia.org/wiki/Vector_projection
    return (dot(from, to) / dot(to, to)) * to;
}

inline matrix3x3 rotation(float angle, const vec3& direction)
{
    const auto n = normalize(direction);
    const auto c = std::cos(angle);
    const auto s = std::sin(angle);

    matrix3x3 result;

    result.row1.x = n.x * n.x * (1 - c) + c;
    result.row1.y = n.x * n.y * (1 - c) + n.z * s;
    result.row1.z = n.x * n.z * (1 - c) - n.y * s;

    result.row2.x = n.x * n.y * (1 - c) - n.z * s;
    result.row2.y = n.y * n.y * (1 - c) + c;
    result.row2.z = n.y * n.z * (1 - c) + n.x * s;

    result.row3.x = n.x * n.z * (1 - c) + n.y * s;
    result.row3.y = n.y * n.z * (1 - c) - n.x * s;
    result.row3.z = n.z * n.z * (1 - c) + c;

    return result;
}

inline matrix4x4 translation(const vec3& v)
{
    matrix4x4 result;

    result.row1.w = v.x;
    result.row2.w = v.y;
    result.row3.w = v.z;

    return result;
}

} // namespace ptm