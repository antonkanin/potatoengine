#pragma once

#include "vertex.hpp"
#include <vector>

namespace pt
{

typedef unsigned int index;

struct uv
{
    float u;
    float v;
};

struct model
{
    std::vector<vertex> vertices;
    std::vector<index>  indices;
    std::vector<uv> texture_uv;
};

} // namespace pt