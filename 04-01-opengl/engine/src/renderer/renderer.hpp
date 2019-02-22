#pragma once

#include <SDL2/SDL.h> // TODO do we really need the full SDL2.h here?
#include <memory>
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

    virtual void load_model(const model& model) = 0;

    virtual void draw_triangle(const model&          model,
                               const transformation& transformation) = 0;

    virtual void swap_buffers() = 0;

protected:
    SDL_Window* window_ = nullptr;
};

std::unique_ptr<renderer> make_renderer();

} // namespace pt