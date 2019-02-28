#pragma once

#include <ostream>

namespace pt
{
struct vector3d
{
    float x;
    float y;
    float z;

    vector3d& operator+=(const vector3d& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;

        return *this;
    }

    vector3d& operator-=(const vector3d& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;

        return *this;
    }
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

inline vector3d operator*(const vector3d lhs, const float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

inline vector3d operator*(const float lhs, const vector3d& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
}

inline std::ostream& operator<<(std::ostream& out, const vector3d& value)
{
    out << value.x << ' ' << value.y << ' ' << value.z;
    return out;
}

} // namespace pt