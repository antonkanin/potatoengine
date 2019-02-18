#pragma once

#include "renderer.hpp"

namespace pt
{

class renderer_opengl final : public renderer
{
public:
    bool initialize(SDL_Window* window) override;

    void draw_triangle(const triangle& tri) override;

    void swap_buffers() override;

private:

};

} // namespace pt