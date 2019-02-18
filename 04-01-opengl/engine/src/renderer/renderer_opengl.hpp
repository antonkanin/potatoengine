#pragma once

#include "renderer.hpp"
#include <SDL2/SDL_opengl.h>

namespace pt
{

class renderer_opengl final : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_triangle(const triangle& tri) override;

    void swap_buffers() override;

private:
    SDL_GLContext gl_context = nullptr;

    GLuint gl_program_id = 0;
};

} // namespace pt