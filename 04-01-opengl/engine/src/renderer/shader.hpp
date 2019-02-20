#pragma once

#include <fstream>
#include <SDL2/SDL_opengl.h>

namespace pt
{

class shader
{
public:
    explicit shader(const std::string& file_name);

    bool compile();

private:
    GLuint shader_id_;
};

} // namespace pt