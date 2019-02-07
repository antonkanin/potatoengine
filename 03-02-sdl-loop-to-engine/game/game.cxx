#include "../engine/include/engine.h"
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

    bool game_running = true;

    while (game_running)
    {
        // main game loop
        pt::Event event;
        while (engine->poll_events(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    process_input(event, "pressed");
                    break;
                }

                case SDL_KEYUP:
                {
                    process_input(event, "lifted");
                    break;
                }

                case SDL_QUIT:
                {
                    game_running = false;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
