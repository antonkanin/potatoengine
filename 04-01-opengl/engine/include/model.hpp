#pragma once

#include "vertex.hpp"
#include <vector>

namespace pt
{

typedef unsigned int index;

struct model
{
    std::vector<vertex> vertices;
    std::vector<index>  indices;
};

} // namespace pt