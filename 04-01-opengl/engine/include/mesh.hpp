#pragma once

#include "texture.hpp"
#include "vertex.hpp"
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

    mesh() = default;

    mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices,
         std::vector<texture> textures);

    void draw(program& program) const;

private:
    unsigned int VAO_ = 0;

    void setup_mesh();
};

} // namespace pt