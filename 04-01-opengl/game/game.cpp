#include "engine.hpp"
#include "space_ship.hpp"

int main(int argc, char* argv[])
{
    auto engine = pt::make_engine();

    engine->set_title("The Witcher 5: Wild Cube");

    if (!engine->init())
    {
        return EXIT_FAILURE;
    }

    auto input_printer_obj = make_space_ship(*engine);

    engine->add_object(move(input_printer_obj));

    engine->run();

    return EXIT_SUCCESS;
}
