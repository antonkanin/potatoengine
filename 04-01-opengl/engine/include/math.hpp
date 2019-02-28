#include <cmath>

#pragma once

#include "vector3d.hpp"
#include <cmath>

namespace pt
{

inline vector3d cross(const vector3d& lhs, const vector3d& rhs)
{
    // clang-format off
    return { lhs.y * rhs.z - lhs.z * rhs.y,
             lhs.z * rhs.x - lhs.x * rhs.z,
             lhs.x * rhs.y - lhs.y * rhs.x };
    // clang-format on
}

inline float dot(const vector3d& lhs, const vector3d& rhs)
{
    return lhs.x * rhs.x + rhs.x * rhs.y + lhs.z * rhs.z;
}

inline float length(const vector3d& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vector3d norm(const vector3d& v)
{
    const auto l = length(v);
    return { v.x / l, v.y / l, v.z / l };
}

inline vector3d projection(const vector3d& from, const vector3d& to)
{
    // https://en.wikipedia.org/wiki/Vector_projection
    return (dot(from, to) / dot(to, to)) * to;
}

} // namespace pt