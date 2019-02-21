#pragma once

#include "vertex.hpp"
#include <cstring>

namespace pt
{

struct model
{
    pt::vertex*     vertices   = nullptr;
    unsigned short  vert_count = 0;
    unsigned short* indices    = nullptr;
    unsigned short  ind_count  = 0;

    model() = default;

    model(const model& source);
};

} // namespace pt