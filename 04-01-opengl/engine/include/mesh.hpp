#include <utility>

#pragma once

#include "../src/renderer/program.hpp" // TODO clean this up
#include "texture.hpp"
#include "vertex.hpp"
#include <vector>

namespace pt
{

struct mesh
{
    std::vector<vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<texture>      textures;

    mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices,
         std::vector<texture> textures);

    void draw(program program);

private:
    unsigned int VAO_ = 0;
    unsigned int VBO_ = 0;
    unsigned int EBO_ = 0;

    void setup_mesh();
};

} // namespace pt