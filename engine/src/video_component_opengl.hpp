#pragma once

#include "video_component.hpp"

namespace pt
{

class video_component_opengl final : public video_component
{
public:
    video_component_opengl();
    ~video_component_opengl();

    bool init(const std::string& title) override;

    void clean_up() override;

    void load_model_into_gpu(std::unique_ptr<class model>& model_ptr) override;

    void render_object(const struct model&          model,
                       const struct transformation& transformation,
                       const struct movable_object& camera,
                       const ptm::vec3& light_position, float time) override;

    void render_light(const class model& model, const ptm::vec3& light_position,
                      const class movable_object& camera) override;

    void render_line(const ptm::vec3& from, const ptm::vec3& to,
                     const ptm::vec3&            color,
                     const class movable_object& camera) override;

    void render_line_ndc(const ptm::vec3& from, const ptm::vec3& to,
                         const ptm::vec3& color) override;

    void swap_buffers() override;

    void enable_vsync(bool state) override;

    void enable_wireframe(bool state) override;

    float get_ticks() override;

    ptm::vec2i get_window_size() const override;

    SDL_Window* get_window() override;

    void lock_cursor(bool is_locked) override;

private:
    std::unique_ptr<class video_component_pimpl> impl;

    void init_alpha_texture();

    void generate_alpha();

    // alpha texture;
    GLubyte*     data_ = nullptr;
    int          w_    = 1000;
    int          h_    = 1000;
    unsigned int textureID;
};

}