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
 TODO: 2) model should not know about the fact that it gets loaded to the vertex
buffer

 */

#pragma once

#include <memory>
#include <vector>

namespace pt
{

using mesh_ptr = std::unique_ptr<class mesh>;

class model
{
public:
    model();
    ~model();

    void draw(class program& program) const;

    void add_mesh(mesh_ptr&);

    std::vector<mesh_ptr>& get_meshes() { return meshes_; }

private:
    std::vector<mesh_ptr> meshes_;
};

} // namespace pt