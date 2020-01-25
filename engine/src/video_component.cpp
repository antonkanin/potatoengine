#include "video_component.hpp"
#include "video_component_opengl.hpp"

namespace pt
{

void video_component::on_window_resize(Sint32 w, Sint32 h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
}

std::unique_ptr<video_component> make_video_component(video_api_type type)
{
    if (type == video_api_type::OPEN_GL)
    {
        std::unique_ptr<video_component> result(new video_component_opengl);
        return result;
    }
    else
    {
        throw std::runtime_error("API not supported");
    }
}

}