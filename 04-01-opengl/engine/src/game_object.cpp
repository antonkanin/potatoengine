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

} // namespace pt