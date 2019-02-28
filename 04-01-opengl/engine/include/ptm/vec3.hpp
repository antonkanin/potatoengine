#pragma once

#include <ostream>

namespace ptm
{

struct vec3
{
    float x;
    float y;
    float z;

    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3& operator+=(const vec3& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;

        return *this;
    }

    vec3& operator-=(const vec3& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;

        return *this;
    }
};

const vec3 zero_vector = { 0.0f, 0.0f, 0.0f };
const vec3 up_vector   = { 0.0f, 1.0f, 0.0f };
const vec3 left_vector = { 1.0f, 0.0f, 0.0f };

inline vec3 operator+(const vec3& lhs, const vec3& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline vec3 operator-(const vec3& lhs, const vec3 rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

inline vec3 operator*(const vec3 lhs, const float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

inline vec3 operator*(const float lhs, const vec3& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
}

inline float operator*(const vec3& lhs, const vec3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline std::ostream& operator<<(std::ostream& out, const vec3& value)
{
    out << value.x << ' ' << value.y << ' ' << value.z;
    return out;
}

} // namespace ptm