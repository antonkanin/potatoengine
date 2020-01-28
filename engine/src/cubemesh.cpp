#include "cubemesh.hpp"

#include "game_object.hpp"
#include "model_utils.hpp"

namespace pt
{

cubemesh::cubemesh(game_object* game_object)
    : game_object_{ game_object }
{
    model_ = load_model_from_file("res/cube/cube_leopard.obj");

    game_object_->get_engine().load_model_into_gpu(model_);
}

} // namespace pt
