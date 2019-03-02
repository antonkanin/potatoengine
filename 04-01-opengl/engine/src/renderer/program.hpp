#pragma once

#include <SDL2/SDL_opengl.h>
#include <string>

namespace pt
{

class program
{
public:
    program(const std::string& vertex_path,
               const std::string& fragment_path);

    ~program();

    GLuint load_shader(const std::string& code, GLenum shader_type);

    void use();

    void validate();

private:
    std::string load_file(const std::string& file_name);

    GLuint make_program(GLuint vertex_id, GLuint fragment_id);

    void delete_shader(GLuint shader_id);

    GLuint program_id_ = 0;
};

} // namespace pt