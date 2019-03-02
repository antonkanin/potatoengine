#pragma once

#include "ptm/vec3.hpp"
#include "ptm/vec2.hpp"

namespace pt
{

struct vertex
{
    ptm::vec3 position;
    ptm::vec2 tex_coords;
};

} // namespace pt