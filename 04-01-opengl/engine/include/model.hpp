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

 */

#pragma once

#include "../src/renderer/program.hpp" // TODO we should not be including private headers
#include "mesh.hpp"
#include "model.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
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

    void load_model(const std::string& path);

    void process_node(aiNode* node, const aiScene* scene);

    static mesh process_mesh(aiMesh* mesh, const aiScene* scene);

    static std::vector<texture> loadMaterialTextures(aiMaterial*        mat,
                                              aiTextureType      type,
                                              const std::string& typeName);
};

} // namespace pt