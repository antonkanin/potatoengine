#pragma once

#include <SDL2/SDL.h> // TODO do we need full SDL2.h here?
#include <memory>

namespace pt
{

struct triangle;

class renderer
{
public:
    virtual bool initialize(SDL_Window* window);

    virtual void draw_triangle(const triangle& tri) = 0;

    virtual void swap_buffers() = 0;

private:
    SDL_Window* window_ = nullptr;
};

std::unique_ptr<renderer> make_renderer();

} // namespace pt