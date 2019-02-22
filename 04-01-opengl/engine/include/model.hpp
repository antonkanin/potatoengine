#pragma once

#include "vertex.hpp"
#include <vector>

namespace pt
{

struct model
{
    std::vector<vertex>       vertices;
    std::vector<unsigned int> indices;
};

} // namespace pt