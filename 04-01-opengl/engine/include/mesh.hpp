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
    mesh();
    ~mesh();

    mesh(const mesh&) = delete;
    mesh& operator=(const mesh&) = delete;

    std::vector<vertex>  vertices;
    std::vector<index>   indices;
    std::vector<texture> textures;

    // std::unique_ptr<vertex_buffer> vertex_buffer_;

/*
    mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices,
         std::vector<texture> textures);
*/

    void draw(program& program) const;

private:
    unsigned int VAO_ = 0;

    void setup_mesh();
};

using mesh_ptr = std::unique_ptr<mesh>;

} // namespace pt