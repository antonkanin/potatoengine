#pragma once

#include "program.hpp"
#include "renderer.hpp"
#include "transformation.hpp"
#include <SDL2/SDL_opengl.h>
#include <mesh.hpp>
#include <model.hpp>

namespace pt
{

class renderer_opengl final : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_triangle(const transformation& transformation,
                       const camera&         camera) override;

    void swap_buffers() override;

    // currently we only support a single mesh
    void load_model(const model &model) override;

private:
    bool get_opengl_context();

    void update_transform_matrix(const transformation& transformation,
                                 const camera&         camera);

    SDL_GLContext gl_context_ = nullptr;

    GLuint texture_id_ = 0;

    GLuint VAO_ = 0;
    GLuint EBO_ = 0;

    GLsizei indecies_count_ = 0;

    std::unique_ptr<program> program_;
};

} // namespace pt