#pragma once

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_stdinc.h>
#include <memory>
#include <ptm/vec2.hpp>
#include <ptm/vec3.hpp>

class SDL_Window;

namespace pt
{

class video_component
{
public:
    video_component();
    ~video_component();

    bool init(const std::string& title);

    void clean_up();

    void load_model(class model& model);

    static void load_model_into_gpu(std::unique_ptr<class model>& model_ptr);

    void render_object(const struct model&          model,
                       const struct transformation& transformation,
                       const struct movable_object& camera,
                       const ptm::vec3& light_position, float time);

    void render_light(const class model& model, const ptm::vec3& light_position,
                      const class movable_object& camera);

    void render_line(const ptm::vec3& from, const ptm::vec3& to,
                     const ptm::vec3&            color,
                     const class movable_object& camera);

    void render_line_ndc(const ptm::vec3& from, const ptm::vec3& to,
                         const ptm::vec3& color);

    void swap_buffers();

    void enable_vsync(bool state);

    void enable_wireframe(bool state);

    float get_ticks();

    ptm::vec2i get_window_size() const;

    SDL_Window* get_window();

    static void on_window_resize(Sint32 w, Sint32 h);

    void lock_cursor(bool is_locked);

private:
    std::unique_ptr<class video_component_pimpl> impl;

    void init_alpha_texture();

    void generate_alpha();

    // alpha texture;
    GLubyte* data_ = nullptr;
    int w_ = 1000;
    int h_ = 1000;
    unsigned int textureID;
};

} // namespace pt