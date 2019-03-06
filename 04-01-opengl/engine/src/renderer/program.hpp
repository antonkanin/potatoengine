#pragma once

#include <SDL2/SDL_opengl.h>
#include <string>
#include "ptm/vec3.hpp"

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

    void set_1i(const std::string& uniform_name, GLint uniform_value);

    void set_vec3(const std::string& uniform_name, ptm::vec3 value);

private:
    std::string load_file(const std::string& file_name);

    GLuint make_program(GLuint vertex_id, GLuint fragment_id);

    GLuint program_id_ = 0;
};

} // namespace pt