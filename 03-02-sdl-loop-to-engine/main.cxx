#include "engine.h"
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
    std::unique_ptr<pt::engine> engine = std::make_unique<pt::engine>();

    engine->init();


    // TODO fix the warning "Warning:(47, 43) Clang-Tidy: Use of a signed
    // integer operand with a binary bitwise operator"
    SDL_Window* window =
        SDL_CreateWindow("SDL Game Loop", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        SDL_Log("Error: failed to SDL window %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    bool game_running = true;

    while (game_running)
    {
        // main game loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
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
