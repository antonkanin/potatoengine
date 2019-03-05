#include "engine.hpp"
#include "game_objects/camera_controller.hpp"
#include "game_objects/show_fps.hpp"
#include "game_objects/space_ship.hpp"
#include "game_objects/vehicle.hpp"

void create_model(pt::engine& engine, const ptm::vec3 shift)
{
    auto m = std::make_unique<space_ship>();
    m->set_position(m->get_position() + shift);
    engine.add_object(move(m));
}

int main(int argc, char* argv[])
{
    auto engine = pt::make_engine();

    engine->set_title("The Witcher 5: Wild Cube");

    if (!engine->init())
    {
        return EXIT_FAILURE;
    }

    create_model(*engine, { 0.f, 0.f, 0.f });
    create_model(*engine, { 5.f, 0.f, 0.f });
    create_model(*engine, { 0.f, 5.f, 0.f });
    create_model(*engine, { 5.f, 5.f, 0.f });

    engine->add_object<camera_controller>();

    // engine->add_object<vehicle>();

    engine->add_object<show_fps>();

    engine->run();

    return EXIT_SUCCESS;
}
