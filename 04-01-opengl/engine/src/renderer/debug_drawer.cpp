#include "debug_drawer.hpp"

namespace pt
{

debug_drawer::debug_drawer(pt::video_component* video_component,
                           movable_object*      camera)
    : video_component_(video_component)
    , camera_(camera)
{
}

    void debug_drawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
    {
        video_component_->render_line(
                /*from*/ { from.x(), from.y(), from.z() },
                /*to*/ { to.x(), to.y(), to.z() },
                /*color*/ { color.x(), color.y(), color.z() },
                /*camera*/ *camera_);
    }

    debug_drawer::~debug_drawer() = default;

} // namespace pt