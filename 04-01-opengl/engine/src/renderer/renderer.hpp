#pragma once

#include "movable_object.hpp"
#include <SDL2/SDL.h> // TODO do we really need the full SDL2.h here?
#include <memory>
#include <mesh.hpp>
#include <model.hpp>
#include <transformation.hpp>

namespace pt
{

struct triangle;

class renderer
{
public:
    virtual ~renderer() = default;

    virtual bool initialize(SDL_Window* window);

    // TODO merge render_modal and render_light into a generic method, add 'material' abstraction
    virtual void render_model(const model &model,
                              const transformation &transformation,
                              const movable_object &camera,
                              const ptm::vec3 &light_position) = 0;

    virtual void render_light(const model &model,
                              const vec3 &light_position,
                              const movable_object &camera) = 0;

    virtual void swap_buffers() = 0;

    virtual void enable_vsync(bool state) = 0;

    virtual void enable_wireframe(bool state) = 0;

    virtual void prepare_gui_frame() = 0;

    virtual void render_gui_frame() = 0;


protected:
    SDL_Window* window_ = nullptr; // we shouldn't be using SDL_Window here as
                                   // it's an implementation detail
};

std::unique_ptr<renderer> make_renderer();

} // namespace pt