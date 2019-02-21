#pragma once

#include <SDL2/SDL_opengl.h>
#include <fstream>

namespace pt
{

class shader
{
public:
    shader(const std::string& file_name, GLenum shader_type);

    GLuint get_shader_id() const;

private:
    static std::string load_from_file(const std::string& file_name);

    bool compile(const std::string& shader_text, GLenum shader_type);

    GLuint shader_id_;
};

} // namespace pt