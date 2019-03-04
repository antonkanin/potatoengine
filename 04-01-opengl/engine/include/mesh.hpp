#include <utility>

#pragma once

#include "../src/renderer/program.hpp" // TODO clean this up
#include "texture.hpp"
#include "vertex.hpp"
#include <vector>

namespace pt
{

typedef unsigned int index;

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