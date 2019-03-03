#pragma once

#include "model.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace pt
{

class model
{
public:
    model() = default;

    model(const std::string& file_name) {}

    void draw(program program) {}

private:
    std::vector<mesh> meshes;
    std::string dictionary;

    void load_model(const std::string& file_name)
    {

    }

    void process_node(aiNode* node, const aiScene* scene)
    {
    }

    void process_mesh(aiMesh* mesh, const aiScene* scene)
    {

    }

    // TODO ... https://learnopengl.com/Model-Loading/Model

};

} // namespace pt