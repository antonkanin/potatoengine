#include "engine.h"
#include "engine_sdl.h"
#include "game_object.h"
#include <cstdlib>
#include <engine.h>
#include <memory>

namespace pt
{

std::unique_ptr<engine> make_engine()
{
    std::unique_ptr<engine> result(new engine_sdl());
    return result;
}

void engine::add_object(game_object* object)
{
    objects_.push_back(object);
}

void engine::update_objects()
{
    for (auto& object : objects_)
    {
        object->update();
    }
}

input_manager& engine::get_input_manager()
{
    return *input_manager_.get();
}

} // namespace pt