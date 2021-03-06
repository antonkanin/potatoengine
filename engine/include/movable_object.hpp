#pragma once

#include "ptm/vec3.hpp"

namespace pt
{

using namespace ptm;

// TODO should the camera just have a transform object to handle position &
// rotation?
class movable_object
{
public:
    vec3 get_direction() const;
    void set_direction(const vec3& direction);

    vec3 get_position() const;
    void set_position(const vec3& position);

    vec3 get_up() const;
    void set_up(const vec3& direction);

    void move_forward(float dist);
    void move_backward(float distance);

    void move_left(float distance);
    void move_right(float distance);

    void move_up(float distance);
    void move_down(float distance);

    void add_yaw(float angle);
    void add_pitch(float angle);

private:
    vec3 direction_ = { 0.f, 0.f, -1.f };
    vec3 up_        = vec3::up();
    vec3 position_  = { 0.f, 0.f, 0.f };
};

} // namespace pt