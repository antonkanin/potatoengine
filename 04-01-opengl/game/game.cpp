#include "engine.hpp"
#include "space_ship.hpp"
#include <memory>

int main(int argc, char* argv[])
{
    auto engine = pt::make_engine();

    if (!engine->init())
    {
        return EXIT_FAILURE;
    }

    auto input_printer_obj = make_input_printer(*engine);

    engine->add_object(move(input_printer_obj));

    engine->run();

    return EXIT_SUCCESS;
}
