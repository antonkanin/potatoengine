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
    virtual ~video_component() = default;

    virtual bool init(const std::string& title) = 0;

    virtual void clean_up() = 0;

    virtual void load_model_into_gpu(std::unique_ptr<class model>& model_ptr) = 0;

    virtual void render_object(const struct model&          model,
                       const struct transformation& transformation,
                       const struct movable_object& camera,
                       const ptm::vec3& light_position, float time) = 0;

    virtual void render_light(const class model& model, const ptm::vec3& light_position,
                      const class movable_object& camera) = 0;

    virtual void render_line(const ptm::vec3& from, const ptm::vec3& to,
                     const ptm::vec3&            color,
                     const class movable_object& camera) = 0;

    virtual void render_line_ndc(const ptm::vec3& from, const ptm::vec3& to,
                         const ptm::vec3& color) = 0;

    virtual void swap_buffers() = 0;

    virtual void enable_vsync(bool state) =0;

    virtual void enable_wireframe(bool state) = 0;

    virtual float get_ticks() = 0;

    virtual ptm::vec2i get_window_size() const = 0;

    virtual SDL_Window* get_window() = 0;

    static void on_window_resize(Sint32 w, Sint32 h);

    virtual void lock_cursor(bool is_locked) = 0;
};

enum class video_api_type
{
    OPEN_GL,
    VULKAN
};

std::unique_ptr<video_component> make_video_component(video_api_type type);

} // namespace pt