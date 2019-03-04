#pragma once

#include "program.hpp"
#include "renderer.hpp"
#include "transformation.hpp"
#include <model.hpp>

namespace pt
{

class renderer_opengl final : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_model(const model& model, const transformation& transformation,
                    const camera& camera) override;

    void swap_buffers() override;

private:
    bool get_opengl_context();

    void update_transform_matrix(const transformation& transformation,
                                 const camera&         camera);

    SDL_GLContext gl_context_ = nullptr;

    std::unique_ptr<program> program_;
};

} // namespace pt