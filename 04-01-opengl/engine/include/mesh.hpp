#pragma once

#include "texture.hpp"
#include "vertex.hpp"
#include <renderer/vb_builder.hpp>
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

    mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices,
         std::vector<texture> textures, vb_builder* vb_builder_value);

    void draw(program& program) const;

private:
    vb_builder* vb_builder_ = nullptr;

    unsigned int VAO_ = 0;

    void setup_mesh();
};

} // namespace pt