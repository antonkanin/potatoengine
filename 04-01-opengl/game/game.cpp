#include "engine.hpp"
#include "show_fps.hpp"
#include "space_ship.hpp"

int main(int argc, char* argv[])
{
    auto engine = pt::make_engine();

    engine->set_title("The Witcher 5: Wild Cube");

    if (!engine->init())
    {
        return EXIT_FAILURE;
    }

    auto space_ship = make_space_ship(*engine);
    engine->add_object(move(space_ship));

    //    auto fps_display = std::make_unique<show_fps>(*engine);
    //    engine->add_object(move(fps_display));

    engine->run();

    return EXIT_SUCCESS;
}
