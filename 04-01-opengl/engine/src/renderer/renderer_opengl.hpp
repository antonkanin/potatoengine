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

    // currently we only support a single model
    void load_model(const model& model) override;

private:
    bool get_opengl_context();

    void update_transform_matrix(const transformation& transformation);

    void load_tecture();

    void validate_program();

    SDL_GLContext gl_context_ = nullptr;

    GLuint gl_program_id_ = 0;

    GLuint vertex_shader_id_ = 0;

    GLuint texture_id_ = 0;

    GLuint VAO_ = 0;
    GLuint EBO_ = 0;

    GLsizei indecies_count_ = 0;
};

} // namespace pt