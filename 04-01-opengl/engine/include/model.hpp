#pragma once

#include "vertex.hpp"

struct model
{
    pt::vertex* vertices;
    unsigned short vert_count;
    unsigned short* indices;
    unsigned short ind_count;
};
