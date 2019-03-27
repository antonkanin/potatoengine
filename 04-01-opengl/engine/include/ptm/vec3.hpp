#pragma once

#include <ostream>

namespace ptm
{

struct vec3
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    constexpr vec3() = default;

    constexpr vec3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

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

    static constexpr vec3 zero() { return { 0.0f, 0.0f, 0.0f }; }
    static constexpr vec3 left() { return { 1.0f, 0.0f, 0.0f }; }
    static constexpr vec3 up() { return { 0.0f, 1.0f, 0.0f }; }

    static constexpr vec3 white() { return { 1.f, 1.f, 1.f }; }
    static constexpr vec3 red() { return { 1.f, 0.f, 0.f }; }
};

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