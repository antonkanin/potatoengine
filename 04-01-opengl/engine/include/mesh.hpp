#pragma once

#include "texture.hpp"
#include "vertex.hpp"
#include <memory>
#include <renderer/vertex_buffer.hpp>
#include <utility>
#include <vector>

namespace pt
{

typedef unsigned int index;

struct program;

struct mesh
{
    std::vector<vertex>  vertices;
    std::vector<index>   indices;
    std::vector<texture> textures;

    std::unique_ptr<vertex_buffer> vertex_buffer_ptr;

    void draw(program& program) const;
};

using mesh_ptr = std::unique_ptr<mesh>;

} // namespace pt