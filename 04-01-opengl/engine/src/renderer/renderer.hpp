#pragma once

#include <SDL2/SDL.h> // TODO do we need full SDL2.h here?
#include "triangle.hpp"

class renderer
{
public:
    virtual bool initialize(SDL_Window* window);

    virtual void draw_triangle(const triangle& tri) = 0;

private:
    SDL_Window* window_ = nullptr;
};