#pragma once

#include "texture_image.hpp"
#include "vertex.hpp"
#include <vector>

namespace pt
{

typedef unsigned int index;

struct model
{
    std::vector<vertex> vertices;
    std::vector<index>  indices;

    texture_image image; // TODO should be using unique_ptr here
};

} // namespace pt