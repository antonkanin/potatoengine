
#include <game_object.hpp>

#include "game_object.hpp"

namespace pt
{

engine& game_object::get_engine()
{
    return engine_;
}

vector3d game_object::get_position() const
{
    return position_;
}

void game_object::set_position(const vector3d& position)
{
    position_ = position;
}

vector3d game_object::get_rotation() const
{
    return rotation_;
}

void game_object::set_roration(const vector3d& rotation)
{
    rotation_ = rotation;
}

} // namespace pt