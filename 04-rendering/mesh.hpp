#pragma once

#include <vector>
#include "point_array.hpp"

typedef std::vector<int> index_array;

struct mesh
{
    point_array points;
    index_array indexes;
};


