#include "game_objects/audio_test.hpp"
#include "game_objects/camera_gui_controller.hpp"
#include "game_objects/camera_keyboard_controller.hpp"
#include "game_objects/cube.hpp"
#include "game_objects/editor/mode_switcher.hpp"
#include "game_objects/editor/object_creator.hpp"
#include "game_objects/editor/object_selector.hpp"
#include "game_objects/game/enemies_spawer.hpp"
#include "game_objects/game/player.hpp"
#include "game_objects/light_controller.hpp"
#include "game_objects/show_fps.hpp"
#include "game_objects/space_ship.hpp"
#include "game_objects/vehicle.hpp"

#include <file_utils.hpp>
#include <ptexception.hpp>

namespace Game
{
void runGame()
{
    auto engine = std::make_unique<pt::engine>();

    // pt::load_scene(*engine, "");

    // return EXIT_SUCCESS;

    engine->set_title("The Witcher 5: Wild Cube");

    engine->init_engine();

    engine->enable_physics(false);
    // engine->enable_vsync(false);

    PT_REGISTER(engine, space_ship);
    PT_REGISTER(engine, vehicle);
    PT_REGISTER(engine, cube);
    PT_REGISTER(engine, enemy);

    pt::load_scene(*engine, "scenes/level01.yaml");

    engine->add_object<light_controller>("Light")->set_position(
        { 1.f, 2.f, 6.f });

    engine->add_object<camera_gui_controller>("Camera GUI")
        ->set_position({ 0.f, 0.f, 6.f });

    engine->add_object<camera_keyboard_controller>("Keyboard Controller");

    engine->add_object<player>("Player");

    // engine->add_object<enemies_spawner>("Enemies spawner");

    // engine->add_object<vehicle>("Car")->set_position({ 30.f, 0.f, -20.f });

    engine->add_object<show_fps>("FPS Display");

    // engine->add_object<audio_test>("Audio test");

    //    engine->add_object<object_selector>("Object Selector");

    engine->add_object<mode_switcher>("mode_switcher");

    engine->add_object<object_creator>("Object Creator");

    engine->run();
}
}; // namespace Game
