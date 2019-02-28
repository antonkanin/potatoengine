#include "camera.hpp"

void pt::camera::move_forward(float distance)
{
    position_ += direction_ * distance;
}
