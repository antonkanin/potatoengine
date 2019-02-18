#pragma once

#include "point_array.hpp"
#include "vertex.hpp"
#include <vector>

typedef std::vector<int> index_array;

struct points_mesh
{
    point_array points;
    index_array indexes;
};

struct vertex_mesh
{
    vertex_array vertexes;
    index_array  indexes;
};
