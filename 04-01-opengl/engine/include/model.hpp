#pragma once

#include "model.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace pt
{

class model
{
public:
    model() = default;

    model(const std::string& file_name) {}

    void draw(program program)
    {
        for (auto& mesh : meshes)
        {
            mesh.draw(program);
        }
    }

private:
    std::vector<mesh> meshes;
    std::string       directory;

    void load_model(const std::string& file_name)
    {
        Assimp::Importer import;
        const aiScene*   scene = import.ReadFile(
            file_name, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
            !scene->mRootNode)
        {
            throw std::runtime_error(
                "Error: failed to read the model from the file: " + file_name +
                ", details: " + import.GetErrorString());
        }

        directory = file_name.substr(0, file_name.find_last_of('/'));

        process_node(scene->mRootNode, scene);
    }

    void process_node(aiNode* node, const aiScene* scene)
    {
        for (unsigned int mesh_index = 0; mesh_index < node->mNumMeshes;
             ++mesh_index)
        {
            auto mesh = scene->mMeshes[node->mMeshes[mesh_index]];
            meshes.push_back(process_mesh(mesh, scene));
        }

        for (unsigned int child_index = 0; child_index < node->mNumChildren;
             ++child_index)
        {
            process_node(node->mChildren[child_index], scene);
        }
    }

    mesh process_mesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<vertex>  vertices;
        std::vector<index>   indices;
        std::vector<texture> textures;

        for (unsigned int vertex_id = 0; vertex_id < mesh->mNumVertices;
             ++vertex_id)
        {
            vertex vertex{};

            vertex.position = { mesh->mVertices[vertex_id].x,
                              mesh->mVertices[vertex_id].y,
                              mesh->mVertices[vertex_id].z };

            if (mesh->mNormals != nullptr)
            {
                // process normals...
            }

            if (mesh->mTextureCoords[0] != nullptr)
            {
                vertex.tex_coords = { mesh->mTextureCoords[0][vertex_id].x,
                                    mesh->mTextureCoords[0][vertex_id].y};
            }
            else
            {
                vertex.tex_coords = {0.f, 0.f};
            }

            vertices.push_back(vertex);
        }

        // process indices
        // ...

        // process materials
        if (mesh->mMaterialIndex >= 0)
        {
            // ...
        }

        return mesh(vertices, indices, textures);
    }

    // TODO ... https://learnopengl.com/Model-Loading/Model
};

} // namespace pt