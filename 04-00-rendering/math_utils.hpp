#pragma once

#include <cassert>

template <typename T>
T lerp(const T& value1, const T& value2, const float t)
{
    assert(t >= 0.0);
    assert(t <= 1.0);
    return value1 + (value2 - value1) * t;
}