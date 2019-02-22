#pragma once

#include "renderer.hpp"
#include "transformation.hpp"
#include <SDL2/SDL_opengl.h>
#include <model.hpp>

namespace pt
{

class renderer_opengl final : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_triangle(const model&          model,
                       const transformation& transformation) override;

    void swap_buffers() override;

private:
    bool get_opengl_context();

    void update_position(const model& model);

    void update_transform_matrix(const model&          model,
                                 const transformation& transformation);

    void validate_program();

    SDL_GLContext gl_context_ = nullptr;

    GLuint gl_program_id_ = 0;

    GLuint vertex_shader_id_ = 0;
};

} // namespace pt