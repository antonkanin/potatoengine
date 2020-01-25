#pragma once

#include "ptm/vec3.hpp"

namespace pt
{

struct transformation
{
    ptm::vec3 position;
    ptm::vec3 rotation_vector;
    float     rotation_angle = 0.0f;
    ptm::vec3 scale;
};

} // namespace pt