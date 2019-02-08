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

void engine::add_object(std::unique_ptr<game_object> object)
{
    objects_.emplace_back(std::move(object));
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
    return *input_manager_;
}

} // namespace pt