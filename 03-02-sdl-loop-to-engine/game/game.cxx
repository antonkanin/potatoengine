#include "engine.h"
#include "input_printer.h"
#include <memory>

int main(int argc, char* argv[])
{
    auto engine = pt::make_engine();

    if (!engine->init())
    {
        return EXIT_FAILURE;
    }

    auto input_printer_obj = new input_printer(*engine.get());

    engine->add_object(input_printer_obj);

    engine->run();

    return EXIT_SUCCESS;
}
