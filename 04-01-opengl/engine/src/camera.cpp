
#include <camera.hpp>

#include "camera.hpp"
#include "ptm/math.hpp"

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

void camera::add_yaw(float angle)
{
    const auto rotation_m = rotation(angle, up_);
    direction_ = rotation_m * direction_;
}

void camera::add_pitch(float angle)
{
    const auto left = cross(direction_, up_);

    const auto rotation_m = rotation(angle, left);

    direction_ = rotation_m * direction_;
}

} // namespace pt