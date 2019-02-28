
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
    direction_            = rotation_m * direction_;
}

void camera::add_pitch(float angle)
{
    const auto left = cross(direction_, up_);

    const auto rotation_m = rotation(angle, left);

    direction_ = rotation_m * direction_;
}

void camera::move_up(float distance)
{
    position_ += distance * up_;
}

void camera::move_down(float distance)
{
    position_ -= distance * up_;
}

vec3 camera::get_direction() const
{
    return direction_;
}

void camera::set_direction(const vec3& direction)
{
    direction_ = direction;
}

vec3 camera::get_position() const
{
    return position_;
}

void camera::set_position(const vec3& position)
{
    position_ = position;
}

vec3 camera::get_up() const
{
    return up_;
}

void camera::set_up(const vec3& direction)
{
    up_ = direction;
}

} // namespace pt