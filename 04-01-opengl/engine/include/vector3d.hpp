#pragma once

struct vector3d
{
    double x;
    double y;
    double z;
};

inline vector3d operator+(const vector3d& lhs, const vector3d& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

inline vector3d operator-(const vector3d& lhs, const vector3d rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}
