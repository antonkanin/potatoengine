#include "renderer_opengl.hpp"

namespace pt
{

void renderer_opengl::draw_triangle(const triangle& tri)
{
    // TODO drawing triangle with open gl...
}

bool renderer_opengl::initialize(SDL_Window* window)
{
    renderer::initialize(window);

    return true;
}

void renderer_opengl::swap_buffers()
{
    // TODO swap opengl buffers
}

} // namespace pt