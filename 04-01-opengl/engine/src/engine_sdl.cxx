#include "engine_sdl.h"
#include "engine_utils.h"
#include <engine_sdl.h>

namespace pt
{

bool engine_sdl::run()
{
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
                    process_event(event.key);
                    break;
                }

                case SDL_KEYUP:
                {
                    process_event(event.key);
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

        update_objects();

        get_input_manager().reset_states();
    }

    return true;
}

bool engine_sdl::init()
{
    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
        return false;
    }

    // TODO fix the warning "Warning:(47, 43) Clang-Tidy: Use of a signed
    // integer operand with a binary bitwise operator"
    window_ =
        SDL_CreateWindow("SDL Game Loop", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (window_ == nullptr)
    {
        SDL_Log("Error: failed to SDL window %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

void engine_sdl::process_event(const SDL_KeyboardEvent& event)
{
    auto code = get_key(event.keysym.sym);

    get_input_manager().key_code_state(code, key_state::pressed) =
        (event.state == SDL_PRESSED);

    get_input_manager().key_code_state(code, key_state::released) =
        (event.state == SDL_RELEASED);
}

engine_sdl::~engine_sdl()
{
    if (window_ != nullptr)
    {
        SDL_DestroyWindow(window_);
    }

    SDL_Quit();
}

} // namespace pt