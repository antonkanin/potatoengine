#pragma once

#include "ptm/vec2.hpp"
#include "ptm/vec3.hpp"

namespace pt
{

struct vertex
{
    ptm::vec3 position;
    ptm::vec2 tex_coords;
    ptm::vec3 color;
    ptm::vec3 normal;

    vertex()
        : position(0.f, 0.f, 0.f)
        , tex_coords(0.f, 0.f)
        , color(ptm::vec3::red())
        , normal(0.f, 0.f, 0.f)
    {
    }
};

} // namespace pt