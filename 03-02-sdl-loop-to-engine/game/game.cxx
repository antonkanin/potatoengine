#include "../engine/include/engine.h"
#include "input_printer.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <sstream>

void print_event(const std::string_view& key_name,
                 const std::string_view& event_type)
{
    std::cout << key_name << ' ' << event_type << '\n';
}

int main(int argc, char* argv[])
{
    auto engine = pt::make_engine();

    engine->init();

    auto input_printer_obj = std::make_unique<input_printer>(engine);

    engine - run

                 SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
