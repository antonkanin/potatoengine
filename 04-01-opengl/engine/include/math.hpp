#include <cmath>

#pragma once

#include "ptm/vec3.hpp"
#include <cmath>

namespace pt
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
    return lhs.x * rhs.x + rhs.x * rhs.y + lhs.z * rhs.z;
}

inline float length(const vec3& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline vec3 norm(const vec3& v)
{
    const auto l = length(v);
    return { v.x / l, v.y / l, v.z / l };
}

inline vec3 projection(const vec3& from, const vec3& to)
{
    // https://en.wikipedia.org/wiki/Vector_projection
    return (dot(from, to) / dot(to, to)) * to;
}



} // namespace pt