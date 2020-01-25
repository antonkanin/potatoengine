#include "model_utils.hpp"

#include "mesh.hpp"
#include "model.hpp"

#include "renderer/opengl_utils.hpp"
#include "renderer/program.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>

namespace pt
{

std::string directory_;

void process_node(model& model, aiNode* node, const aiScene* scene,
                  const std::string& directory);

mesh_ptr process_mesh(aiMesh* mesh, const aiScene* scene,
                      const std::string& directory);

std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                          const std::string& typeName,
                                          const std::string& directory);

unsigned int TextureFromFile(const char* path, const std::string& directory,
                             bool gamma = false);

std::unique_ptr<model> load_model_from_file(const std::string& path)
{

    Assimp::Importer import;
    const aiScene*   scene =
        import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        throw std::runtime_error(
            "Error: failed to read the model from the file: " + path +
            ", details: " + import.GetErrorString());
    }

    auto directory = path.substr(0, path.find_last_of('/'));

    auto model_object = std::make_unique<model>();

    process_node(*model_object.get(), scene->mRootNode, scene, directory);

    return std::move(model_object);
}

void process_node(model& model, aiNode* node, const aiScene* scene,
                  const std::string& directory)
{
    for (unsigned int mesh_index = 0; mesh_index < node->mNumMeshes;
         ++mesh_index)
    {
        auto ai_mesh = scene->mMeshes[node->mMeshes[mesh_index]];
        auto pt_mesh = process_mesh(ai_mesh, scene, directory);
        model.add_mesh(pt_mesh);
    }

    for (unsigned int child_index = 0; child_index < node->mNumChildren;
         ++child_index)
    {
        process_node(model, node->mChildren[child_index], scene, directory);
    }
}

mesh_ptr process_mesh(aiMesh* mesh, const aiScene* scene,
                      const std::string& directory)
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
            vertex.normal = { mesh->mNormals[vertex_id].x,
                              mesh->mNormals[vertex_id].y,
                              mesh->mNormals[vertex_id].z };
        }

        if (mesh->mTextureCoords[0] != nullptr)
        {
            vertex.tex_coords = { mesh->mTextureCoords[0][vertex_id].x,
                                  mesh->mTextureCoords[0][vertex_id].y };
        }
        else
        {
            vertex.tex_coords = { 0.f, 0.f };
        }

        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int face_id = 0; face_id < mesh->mNumFaces; ++face_id)
    {
        aiFace face = mesh->mFaces[face_id];
        for (unsigned int index_id = 0; index_id < face.mNumIndices; ++index_id)
        {
            indices.push_back(face.mIndices[index_id]);
        }
    }

    // process materials
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<texture> diffuseMaps = loadMaterialTextures(
            material, aiTextureType_DIFFUSE, "texture_diffuse", directory);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<texture> specularMaps = loadMaterialTextures(
            material, aiTextureType_SPECULAR, "texture_specular", directory);

        textures.insert(textures.end(), specularMaps.begin(),
                        specularMaps.end());

        // reading diffuse color
        aiColor3D diffuse_color;
        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse_color))
        {
            for (auto& v : vertices)
            {
                v.color = { diffuse_color.r, diffuse_color.g, diffuse_color.b };
            }
        }
    }

    auto result_mesh      = std::make_unique<pt::mesh>();
    result_mesh->vertices = vertices;
    result_mesh->indices  = indices;
    result_mesh->textures = textures;

    return result_mesh;
}

std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                          const std::string& typeName,
                                          const std::string& directory)
{
    std::vector<texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        texture texture;
        texture.id   = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        textures.push_back(texture);
    }
    return textures;
}

unsigned int TextureFromFile(const char* path, const std::string& directory,
                             bool gamma)
{
    std::string filename = std::string(path);
    filename             = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    check_gl_errors();

    int width, height, nrComponents;

    unsigned char* data =
        stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        check_gl_errors();

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        check_gl_errors();

        // glGenerateMipmap(GL_TEXTURE_2D); // TODO turn on MIPMAPS

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        check_gl_errors();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        check_gl_errors();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        check_gl_errors();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        check_gl_errors();

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void draw_mesh(const mesh_ptr& mesh, program& program)
{
    auto buffer_ptr =
        dynamic_cast<vertex_buffer_opengl*>(mesh->vertex_buffer_ptr.get());

    unsigned int VAO_ = buffer_ptr->VAO_;

    check_gl_errors();

    for (unsigned int tex_index = 0; tex_index < mesh->textures.size();
         ++tex_index)
    {
        if (program.set_1i("albedo_texture", tex_index + 1))
        {
            // TODO "+1" here is a horrible hack, we are basically reserved 0
            // for the alpha texture used in hair rendering
            glActiveTexture_(GL_TEXTURE0 + tex_index + 1);
            glBindTexture(GL_TEXTURE_2D, mesh->textures[tex_index].id);
            check_gl_errors();
        }
    }

    glBindVertexArray(VAO_);
    check_gl_errors();

    //    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
    //                   GL_UNSIGNED_INT, nullptr);
    glDrawElementsInstanced(GL_TRIANGLES,
                            static_cast<GLsizei>(mesh->indices.size()),
                            GL_UNSIGNED_INT, nullptr, 64);

    check_gl_errors();

    glBindVertexArray(0);
    check_gl_errors();
}

using model_ptr = std::unique_ptr<model>;

void draw_model(std::unique_ptr<model>& model_ptr, class program& program)
{
    for (auto& mesh : model_ptr->get_meshes())
    {
        draw_mesh(mesh, program);
    }
}

void draw_model(const model& model, class program& program)
{
    for (auto& mesh : model.get_meshes())
    {
        draw_mesh(mesh, program);
    }

}


} // namespace pt
