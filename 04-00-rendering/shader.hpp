#pragma once

#include "points_mesh.hpp"

template <typename Func>
inline vertex_array apply_vertex_shader(const vertex_array& vertexes,
                                        Func                vertex_shader)
{
    vertex_array result = vertexes;

    for (auto& v : result)
    {
        v = vertex_shader(v);
    }

    return result;
}

template <typename Func>
inline void apply_fragment_shader(vertex_array& vertexes, Func fragment_shader)
{
    for (auto& v : vertexes)
    {
        v.c = fragment_shader(v);
    }
}
