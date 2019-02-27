#include "engine.hpp"
#include "engine_sdl.hpp"
#include "game_object.hpp"
#include "renderer/triangle.hpp"
#include <cstdlib>
#include <engine.hpp>
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

void engine::render_objects()
{
    for (auto& object : objects_)
    {
        render_object(object->get_model(), object->get_transformation());
    }
}

void engine::set_title(const std::string& title)
{
    game_title_ = title;
}

void engine::start_objects()
{
    for (auto& object : objects_)
    {
        object->start();
    }
}

bool engine::run()
{
    game_running_ = true;

    start_objects();

    load_models();

    while (game_running_)
    {
        poll_events();

        update_objects();

        render_objects();

        // swap buffers
        post_render_objects();

        // TODO shoudl this be moved to the engine implementation?
        get_input_manager().reset_states();
    }

    return true;
}

void engine::set_game_running(const bool is_game_running)
{
    game_running_ = is_game_running;
}

} // namespace pt