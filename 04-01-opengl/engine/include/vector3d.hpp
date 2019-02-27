#pragma once

namespace pt
{
struct vector3d
{
    float x;
    float y;
    float z;
};


const vector3d zero_vector = { 0.0f, 0.0f, 0.0f };
const vector3d up_vector   = { 0.0f, 1.0f, 0.0f };
const vector3d left_vector = { 1.0f, 0.0f, 0.0f };

inline vector3d operator+(const vector3d& lhs, const vector3d& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline vector3d operator-(const vector3d& lhs, const vector3d rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

} // namespace pt