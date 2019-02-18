#pragma once

struct vector3d
{
    float x;
    float y;
    float z;
};

inline vector3d operator+(const vector3d& lhs, const vector3d& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline vector3d operator-(const vector3d& lhs, const vector3d rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}
