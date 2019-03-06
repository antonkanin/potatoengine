
#include <movable_object.hpp>

#include "movable_object.hpp"
#include "ptm/math.hpp"

namespace pt
{

void pt::movable_object::move_forward(float distance)
{
    position_ += direction_ * distance;
}

void movable_object::move_backward(float distance)
{
    position_ -= direction_ * distance;
}

void pt::movable_object::move_left(float distance)
{
    const auto shift = cross(direction_, up_) * distance;
    position_ -= shift;
}

void movable_object::move_right(float distance)
{
    const auto shift = cross(direction_, up_) * distance;
    position_ += shift;
}

void movable_object::add_yaw(float angle)
{
    const auto rotation_m = rotation(angle, up_);
    direction_            = rotation_m * direction_;
}

void movable_object::add_pitch(float angle)
{
    const auto left = cross(direction_, up_);

    const auto rotation_m = rotation(angle, left);

    direction_ = rotation_m * direction_;
}

void movable_object::move_up(float distance)
{
    position_ += distance * up_;
}

void movable_object::move_down(float distance)
{
    position_ -= distance * up_;
}

vec3 movable_object::get_direction() const
{
    return direction_;
}

void movable_object::set_direction(const vec3& direction)
{
    direction_ = direction;
}

vec3 movable_object::get_position() const
{
    return position_;
}

void movable_object::set_position(const vec3& position)
{
    position_ = position;
}

vec3 movable_object::get_up() const
{
    return up_;
}

void movable_object::set_up(const vec3& direction)
{
    up_ = direction;
}

} // namespace pt