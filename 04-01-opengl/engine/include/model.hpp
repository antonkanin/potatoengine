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

private:
    std::vector<mesh> meshes;
    std::string       directory;

    void load_model(const std::string& path);

    void process_node(aiNode* node, const aiScene* scene);

    mesh process_mesh(aiMesh* mesh, const aiScene* scene);

    std::vector<texture> loadMaterialTextures(aiMaterial*        mat,
                                              aiTextureType      type,
                                              const std::string& typeName);
};

} // namespace pt