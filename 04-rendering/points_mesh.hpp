#pragma once

#include <vector>
#include "point_array.hpp"
#include "vertex.hpp"

typedef std::vector<int> index_array;

struct points_mesh
{
    point_array points;
    index_array indexes;
};

struct vertex_mesh
{
    vertex_array vertexes;
    index_array indexes;
};



