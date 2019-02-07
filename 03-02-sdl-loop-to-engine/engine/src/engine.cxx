#include "engine.h"
#include "engine_sdl.h"
#include "engine_utils.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <engine.h>
#include <memory>

namespace pt
{

std::unique_ptr<engine> make_engine()
{
    return std::make_unique<engine_sdl>();
}

void engine::run()
{
    bool game_running = true;

    while (game_running)
    {
        // main game loop
        pt::event event;
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
}
} // namespace pt