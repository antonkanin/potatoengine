#include "engine.hpp"
#include "game_objects/camera_gui_controller.hpp"
#include "game_objects/camera_keyboard_controller.hpp"
#include "game_objects/light_controller.hpp"
#include "game_objects/show_fps.hpp"
#include "game_objects/space_ship.hpp"
#include "game_objects/vehicle.hpp"
#include "game_objects/audio_test.hpp"

int main(int argc, char* argv[])
{
    auto engine = std::make_unique<pt::engine>();

    engine->set_title("The Witcher 5: Wild Cube");

    if (!engine->init_engine())
    {
        return EXIT_FAILURE;
    }

    // clang-format off

    engine->add_object<space_ship>()
            ->set_position({ -3.f, 3.f, -5.f })
            ->add_body(true);

    engine->add_object<space_ship>()
            ->set_position({ -3.f, -5.f, -5.f })
            ->set_scale({2.f, .1f, 2.f})
            ->add_body(false);
//
//    engine->add_object<space_ship>()
//            ->set_position({ -3.f, 4.f, 0.f });
//
//    engine->add_object<space_ship>()
//            ->set_position({ -3.f, 4.f, 5.f });


    engine->add_object<light_controller>()
            ->set_position({ 3.f, 0.f, 0.f });

    engine->add_object<camera_gui_controller>()->
            set_position({ 0.f, 0.f, 6.f });

    engine->add_object<camera_keyboard_controller>();

    //engine->add_object<vehicle>()->set_position({ 10.f, 0.f, 6.f });

    engine->add_object<show_fps>();

    engine->add_object<audio_test>();

    // clang-format on

    engine->run();

    return EXIT_SUCCESS;
}
