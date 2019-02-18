#include "renderer.hpp"
#include "renderer_opengl.hpp"

namespace pt
{

bool renderer::initialize(SDL_Window* window)
{
    window_ = window;

    return true;
}

std::unique_ptr<renderer> make_renderer()
{
    std::unique_ptr<renderer> result(new renderer_opengl());
    return result;
}

} // namespace pt