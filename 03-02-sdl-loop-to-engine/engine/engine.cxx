#include "include/engine.h"
#include "include/engine_utils.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <memory>

namespace pt
{

class Engine_SDL : public engine
{
public:
    bool init() override
    {
        const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
        if (init_result != 0)
        {
            SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
            return false;
        }

        // TODO fix the warning "Warning:(47, 43) Clang-Tidy: Use of a signed
        // integer operand with a binary bitwise operator"
        window_ = SDL_CreateWindow("SDL Game Loop", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, 800, 600,
                                   SDL_WINDOW_OPENGL);

        if (window_ == nullptr)
        {
            SDL_Log("Error: failed to SDL window %s", SDL_GetError());
            SDL_Quit();
            return false;
        }

        return true;
    }

    bool poll_events(Event& ev) override
    {
        SDL_Event sdl_event;
        if (SDL_PollEvent(&sdl_event))
        {
            auto key   = get_key(sdl_event.key.keysym.sym);
            auto state = get_keystate(sdl_event.key.state);

            ev = { key, state };

            return true;
        }

        return false;
    }

    void process_input(const Event& ev) override {}

private:
    SDL_Window* window_;
};

std::unique_ptr<engine> make_engine()
{
    return std::make_unique<Engine_SDL>();
}

} // namespace pt