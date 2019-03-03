#include "mesh.hpp"

#include "renderer/opengl_utils.hpp"

namespace pt
{

mesh::mesh(std::vector<pt::vertex> vertices, std::vector<unsigned int> indices,
           std::vector<pt::texture> textures)
    : vertices(std::move(vertices))
    , indices(std::move(indices))
    , textures(std::move(textures))
{
    setup_mesh();
}

void mesh::setup_mesh()
{
    ///////////////////////////////////////////////////////////////////////////
    // generate buffers
    glGenVertexArrays(1, &VAO_);
    check_gl_errors();

    glGenBuffers(1, &VBO_);
    check_gl_errors();

    glGenBuffers(1, &EBO_);
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // bind buffers

    glBindVertexArray(VAO_);
    check_gl_errors();

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    check_gl_errors();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex),
                 vertices.data(), GL_STATIC_DRAW);
    check_gl_errors();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    check_gl_errors();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    ///////////////////////////////////////////////////////////////////////////
    // setup attributes

    // position
    glEnableVertexAttribArray(0); // can we use name instead of a number?
    check_gl_errors();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    check_gl_errors();

    // texture
    glEnableVertexAttribArray(1);
    check_gl_errors();

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void*)(3 * sizeof(ptm::vec3)));
    check_gl_errors();

    // normals
    // TODO...

    glBindVertexArray(0);
}

void mesh::draw(pt::program program)
{
    for (unsigned int tex_index = 0; tex_index < textures.size(); ++tex_index)
    {
        program.set_1i("texture", tex_index);
        glBindTexture(GL_TEXTURE_2D, textures[tex_index].id);
        check_gl_errors();
    }

    glActiveTexture(GL_TEXTURE0);
    check_gl_errors();

    glBindVertexArray(VAO_);
    check_gl_errors();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    check_gl_errors();

    glBindVertexArray(0);
    check_gl_errors();
}

} // namespace pt