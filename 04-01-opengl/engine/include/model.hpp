/*
 class model()
~~~~~~~~~~~~~

load_model(...)

  directory_ = ...

  process_node(...)

    process_mesh(..)

      loadMaterialTextures(...) <- uses "directory_"


vextures[];


model load flow

1) load all textures
2) load all meshes

 TODO: 1) remove model loading logic form the model class
 TODO: 2) model should not know about the fact that it gets loaded to the vertex buffer

 */

#pragma once

#include "../src/renderer/program.hpp" // TODO we should not be including private headers
#include "mesh.hpp"
#include "model.hpp"
#include <vector>

namespace pt
{

class model
{
public:
    model() = default;

    explicit model(const std::string& path);

    void draw(program& program) const;

    void add_mesh(const mesh& mesh);

    std::vector<mesh>& get_meshes() { return meshes_; }

private:
    std::vector<mesh> meshes_;
    std::string       directory_;
};

} // namespace pt