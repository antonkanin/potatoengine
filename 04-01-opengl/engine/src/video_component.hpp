#pragma once

#include "ptm/vec3.hpp"
#include <memory>

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

    void render_object(const class model&          model,
                       const class transformation& transformation,
                       const class movable_object& camera,
                       const ptm::vec3&            light_position);

    void render_light(const class model& model, const ptm::vec3& light_position,
                      const class movable_object& camera);

    void swap_buffers();

    void enable_vsync(bool state);

    void enable_wireframe(bool state);

    float get_ticks();

    SDL_Window* get_window();

private:
    std::unique_ptr<class video_component_pimpl> pimpl_;
};

} // namespace pt