#pragma once

#include "vertex.hpp"
#include <cstring>

namespace pt
{

struct model
{
    pt::vertex*     vertices   = nullptr;
    size_t          vert_count = 0;
    unsigned short* indices    = nullptr;
    size_t          ind_count  = 0;

    model() = default;

    model(const model& source);

    model& operator=(const model& source);
};

} // namespace pt