
#include <game_object.hpp>

#include "game_object.hpp"

namespace pt
{

engine& game_object::get_engine()
{
    return *engine_;
}

void game_object::set_position(const ptm::vec3& position)
{
    transformation_.position = position;
}

const model& game_object::get_model() const
{
    return model_;
}

void game_object::set_model(const model& model)
{
    has_model_ = true;
    model_     = model;
}

const transformation& game_object::get_transformation() const
{
    return transformation_;
}

void game_object::set_transform(const transformation& transform)
{
    transformation_ = transform;
}

void game_object::set_rotation(const ptm::vec3& rotation_vector, float angle)
{
    transformation_.rotation_vector = rotation_vector;
    transformation_.rotation_angle  = angle;
}

ptm::vec3 game_object::get_position() const
{
    return transformation_.position;
}

void game_object::load_model(const std::string& path)
{
    set_model(model(path));
}

game_object::~game_object()
{
    engine_ = nullptr;
}

void game_object::set_scale(const ptm::vec3& scale)
{
    transformation_.scale = scale;
}

ptm::vec3 game_object::get_scale() const
{
    return transformation_.scale;
};

} // namespace pt