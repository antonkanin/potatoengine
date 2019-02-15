#include "color.hpp"

color lerp(const color& color1, const color& color2, const float t)
{
    return { lerp(color1.r, color2.r, t), lerp(color1.g, color2.g, t),
             lerp(color1.b, color2.b, t) };
}
