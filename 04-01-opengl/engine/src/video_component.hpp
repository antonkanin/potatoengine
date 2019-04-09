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

    void generate_alpha();

    // alpha texture;
    GLubyte* data_ = nullptr;
    int w_ = 500;
    int h_ = 500;
};

} // namespace pt