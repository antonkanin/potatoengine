#include "game_objects/audio_test.hpp"
#include "game_objects/camera_gui_controller.hpp"
#include "game_objects/camera_keyboard_controller.hpp"
#include "game_objects/cube.hpp"
#include "game_objects/light_controller.hpp"
#include "game_objects/object_creator.hpp"
#include "game_objects/object_selector.hpp"
#include "game_objects/show_fps.hpp"
#include "game_objects/space_ship.hpp"
#include "game_objects/vehicle.hpp"

#include <file_utils.hpp>

int main(int argc, char* argv[])
{
    auto engine = std::make_unique<pt::engine>();

    // pt::load_scene(*engine, "");

    // return EXIT_SUCCESS;

    engine->set_title("The Witcher 5: Wild Cube");

    if (!engine->init_engine())
    {
        return EXIT_FAILURE;
    }

    REGISTER(engine, space_ship);
    REGISTER(engine, vehicle);
    REGISTER(engine, cube);

    // clang-format off

    pt::load_scene(*engine, "scenes/level01.yaml");

    //pt::save_scene(*engine, "scenes/level02.yaml");

//    engine->add_object<space_ship>("Space ship 1")
//            ->set_position({ -3.f, 3.f, -5.f })
//            ->add_body(true);
//
//    engine->add_object<space_ship>("Space ship 2")
//            ->set_position({ -3.f, -5.f, -5.f })
//            ->set_scale({2.f, .1f, 2.f})
//            ->add_body(false);
//
//    engine->add_object<space_ship>()
//            ->set_position({ -3.f, 4.f, 0.f });
//
//    engine->add_object<space_ship>()
//            ->set_position({ -3.f, 4.f, 5.f });


//    engine->add_object<light_controller>("Light")
//            ->set_position({ 3.f, 0.f, 0.f });

    engine->add_object<camera_gui_controller>("Camera GUI")->
            set_position({ 0.f, 0.f, 6.f });

    engine->add_object<camera_keyboard_controller>("Keyboard Controller");

//    engine->add_object<vehicle>("Car")->set_position({ 10.f, 0.f, 6.f });

    engine->add_object<show_fps>("FPS Display");

    //engine->add_object<audio_test>();

    engine->add_object<object_selector>("Object Selector");
    engine->add_object<object_creator>("Object Creator");

    // clang-format on

    engine->run();

    return EXIT_SUCCESS;
}
