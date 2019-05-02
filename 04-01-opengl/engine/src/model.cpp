#include "model.hpp"

#include "renderer/opengl_utils.hpp"
#include <iostream>
#include <log_utils.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace pt
{

unsigned int TextureFromFile(const char* path, const std::string& directory,
                             bool gamma = false)
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

model::model(const std::string& path)
{
    load_model(path);
}

std::vector<texture> model::loadMaterialTextures(aiMaterial*        mat,
                                                 aiTextureType      type,
                                                 const std::string& typeName)
{
    std::vector<texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        texture texture;
        texture.id   = TextureFromFile(str.C_Str(), directory_);
        texture.type = typeName;
        textures.push_back(texture);
    }
    return textures;
}

mesh model::process_mesh(aiMesh* mesh, const aiScene* scene)
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
            material, aiTextureType_DIFFUSE, "texture_diffuse");

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<texture> specularMaps = loadMaterialTextures(
            material, aiTextureType_SPECULAR, "texture_specular");

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

    return { vertices, indices, textures, nullptr};
}

void model::load_model(const std::string& path)
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

    directory_ = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void model::process_node(aiNode* node, const aiScene* scene)
{
    for (unsigned int mesh_index = 0; mesh_index < node->mNumMeshes;
         ++mesh_index)
    {
        auto mesh = scene->mMeshes[node->mMeshes[mesh_index]];
        meshes_.push_back(process_mesh(mesh, scene));
    }

    for (unsigned int child_index = 0; child_index < node->mNumChildren;
         ++child_index)
    {
        process_node(node->mChildren[child_index], scene);
    }
}

void model::draw(program& program) const
{
    for (auto& mesh : meshes_)
    {
        mesh.draw(program);
    }
}

void model::add_mesh(const mesh& mesh)
{
    meshes_.push_back(mesh);
}

} // namespace pt