#include "camera_constoller.hpp"
#include "engine.hpp"
#include "show_fps.hpp"
#include "space_ship.hpp"

void create_model(pt::engine& engine, const ptm::vec3 shift)
{
    auto m = make_model(engine);
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

    auto c = pt::make_object<camera_controller>(*engine);
    engine->add_object(move(c));

    //    auto fps_display = std::make_unique<show_fps>(*engine);
    //    engine->add_object(move(fps_display));

    engine->run();

    return EXIT_SUCCESS;
}
