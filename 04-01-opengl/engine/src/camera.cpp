#include "camera.hpp"
#include "math.hpp"

namespace pt
{

void pt::camera::move_forward(float distance)
{
    position_ += direction_ * distance;
}

void camera::move_backward(float distance)
{
    position_ -= direction_ * distance;
}

void pt::camera::move_left(float distance)
{
    const auto shift = cross(direction_, up_) * distance;
    position_ -= shift;
}

void camera::move_right(float distance)
{
    const auto shift = cross(direction_, up_) * distance;
    position_ += shift;
}

    void camera::turn_right(float angle)
    {


    }

} // namespace pt