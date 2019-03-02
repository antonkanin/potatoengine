#pragma once

#include <SDL2/SDL_opengl.h>
#include <fstream>
#include "opengl_utils.hpp"

namespace pt
{

class shader
{
public:
    shader(const std::string& file_name, GLenum shader_type);

    ~shader();

    GLuint get_shader_id() const;

private:
    static std::string load_from_file(const std::string& file_name);

    bool compile(const std::string& shader_text, GLenum shader_type);

    GLuint shader_id_;
};

class shader_new
{
public:
    shader_new(const std::string& vertex_path, const std::string& fragment_path);

    ~shader_new();

    GLuint load_shader(const std::string& code, GLenum shader_type);

    void use();
private:
    std::string load_file(const std::string& file_name);

    GLuint make_program(GLuint vertex_id, GLuint fragment_id);

    void delete_shader(GLuint shader_id);

    GLuint program_id_ = 0;
};

} // namespace pt