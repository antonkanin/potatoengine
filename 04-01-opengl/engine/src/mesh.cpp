#include "mesh.hpp"

#include "renderer/opengl_utils.hpp"
#include "renderer/program.hpp"

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
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    ///////////////////////////////////////////////////////////////////////////
    // generate buffers
    glGenVertexArrays(1, &VAO_);
    check_gl_errors();

    glGenBuffers(1, &VBO);
    check_gl_errors();

    glGenBuffers(1, &EBO);
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // bind buffers

    glBindVertexArray(VAO_);
    check_gl_errors();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    check_gl_errors();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex),
                 vertices.data(), GL_STATIC_DRAW);
    check_gl_errors();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    check_gl_errors();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);
    check_gl_errors();

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
                          (void*)(sizeof(ptm::vec3)));
    check_gl_errors();

    // color
    glEnableVertexAttribArray(2);
    check_gl_errors();

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void*)(sizeof(ptm::vec3) + sizeof(ptm::vec2)));
    check_gl_errors();

    // normals
    glEnableVertexAttribArray(3);
    check_gl_errors();

    glVertexAttribPointer(
        3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
        (void*)(sizeof(ptm::vec3) + sizeof(ptm::vec2) + sizeof(ptm::vec3)));
    check_gl_errors();

    glBindVertexArray(0);
    check_gl_errors();
}

void mesh::draw(pt::program& program) const
{
    check_gl_errors();

    for (unsigned int tex_index = 0; tex_index < textures.size(); ++tex_index)
    {
        if (program.set_1i("albedo_texture", tex_index + 1))
        {
            glActiveTexture_(GL_TEXTURE0 + tex_index + 1);
            glBindTexture(GL_TEXTURE_2D, textures[tex_index].id);
            check_gl_errors();
        }
    }

    glBindVertexArray(VAO_);
    check_gl_errors();

    //    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
    //                   GL_UNSIGNED_INT, nullptr);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(indices.size()),
                            GL_UNSIGNED_INT, nullptr, 64);

    check_gl_errors();

    glBindVertexArray(0);
    check_gl_errors();
}

} // namespace pt