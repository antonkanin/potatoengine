#pragma once

#include "points_mesh.hpp"

typedef void (*vertex_shader_func)(vertex&);

typedef color (*fragment_shader_func)(const vertex&);

inline void apply_vertex_shader(vertex_array&      vertexes,
                                vertex_shader_func vertex_shader)
{
    for (auto& v : vertexes)
    {
        vertex_shader(v);
    }
}

inline void apply_fragment_shader(vertex_array&        vertexes,
                                  fragment_shader_func fragment_shader)
{
    for (auto& v : vertexes)
    {
        v.c = fragment_shader(v);
    }
}
