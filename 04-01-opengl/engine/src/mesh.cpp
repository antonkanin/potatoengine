#include "mesh.hpp"

#include "renderer/opengl_utils.hpp"
#include "renderer/program.hpp"

namespace pt
{

void mesh::draw(pt::program& program) const
{
    auto buffer_ptr =
        dynamic_cast<vertex_buffer_opengl*>(vertex_buffer_ptr.get());

    unsigned int VAO_ = buffer_ptr->VAO_;

    check_gl_errors();

    for (unsigned int tex_index = 0; tex_index < textures.size(); ++tex_index)
    {
        if (program.set_1i("albedo_texture", tex_index + 1))
        {
            // TODO "+1" here is a horrible hack, we are basically reserved 0
            // for the alpha texture used in hair rendering
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