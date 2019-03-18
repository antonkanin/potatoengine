#include "debug_drawer.hpp"

namespace pt
{

debug_drawer::debug_drawer(pt::video_component* video_component,
                           movable_object*      camera)
    : video_component_(video_component)
    , camera_(camera)
{
}

debug_drawer::~debug_drawer() = default;

} // namespace pt