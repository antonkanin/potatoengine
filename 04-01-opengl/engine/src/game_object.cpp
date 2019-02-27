#include "game_object.hpp"

namespace pt
{

engine& game_object::get_engine()
{
    return engine_;
}

void game_object::set_position(const vector3d& position)
{
    transformation_.position = position;
}

const model& game_object::get_model() const
{
    return model_;
}

void game_object::set_model(const model& model)
{
    model_ = model;
}

const transformation& game_object::get_transformation() const
{
    return transformation_;
}

void game_object::set_transform(const transformation& transform)
{
    transformation_ = transform;
}

void game_object::set_rotation(const vector3d& rotation_vector, float angle)
{
    transformation_.rotation_vector = rotation_vector;
    transformation_.rotation_angle  = angle;
}

} // namespace pt