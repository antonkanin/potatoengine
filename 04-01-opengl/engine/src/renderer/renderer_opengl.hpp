#pragma once

#include "renderer.hpp"
#include <memory>

namespace pt
{

class renderer_opengl : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_triangle(const triangle& tri) override;

    void swap_buffers() override;
};

} // namespace pt