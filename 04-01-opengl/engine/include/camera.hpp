#pragma once

#include "vector3d.hpp"

namespace pt
{
// TODO should the camera just have a transform object to handle position &
// rotation?

class camera
{
public:
    vector3d get_direction() const { return direction_; }
    void     set_direction(const vector3d& direction) {}

    vector3d get_position() const { return position_; }
    void     set_position(const vector3d& position) {}

    vector3d get_up() const { return up_; }
    void     set_up(const vector3d& direction) { up_ = direction; }

    void move_forward(float distance);
    void move_backward(float distance);

    void move_left(float distance);
    void move_right(float distance);

    void move_up(float distance) {}
    void move_down(float distance) {}

    void turn_right(float angle);


    void turn_left(float angle)
    {

    }

private:
    vector3d direction_ = { 0.f, 0.f, -1.f };
    vector3d up_        = up_vector;
    vector3d position_  = { 0.f, 0.f, 0.f };
};

} // namespace pt