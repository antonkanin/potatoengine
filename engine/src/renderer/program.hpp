#pragma once

#include "ptm/vec3.hpp"
#include <SDL2/SDL_opengl.h>
#include <string>

namespace pt
{

class program
{
public:
    program(const std::string& vertex_path, const std::string& fragment_path);

    ~program();

    void use();

    void validate();

    void set_matrix4(const std::string& uniform_name,
                     const GLfloat*     uniform_value);

    bool set_1i(const std::string& uniform_name, GLint uniform_value);

    bool set_1f(const std::string& uniform_name, GLfloat uniform_value);

    void set_vec3(const std::string& uniform_name, ptm::vec3 value);

    GLuint id() const;

private:
    GLuint make_program(GLuint vertex_id, GLuint fragment_id);

    GLuint program_id_ = 0;
};

} // namespace pt