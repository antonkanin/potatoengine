#pragma once

#include "program.hpp"
#include "renderer.hpp"
#include "transformation.hpp"
#include <model.hpp>
#include <glm/detail/type_mat.hpp>

namespace pt
{

class renderer_opengl final : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_model(const model &model, const transformation &transformation, const movable_object &camera,
                        const ptm::vec3 &light_position) override;

    void swap_buffers() override;

    void enable_vsync(bool state) override;

    void prepare_gui_frame() override;
    void render_gui_frame() override;

private:
    bool create_opengl_context();

    glm::mat4 get_transform_matrix(const transformation &transformation,
                                   const movable_object &camera);

    void init_imgui(SDL_Window* window);

    SDL_GLContext gl_context_ = nullptr;

    std::unique_ptr<program> generic_program_;
    std::unique_ptr<program> light_program_;
};

} // namespace pt