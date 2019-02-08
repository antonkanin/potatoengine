#pragma once

#include "engine.h"
#include <SDL2/SDL.h>

namespace pt
{

class engine_sdl : public engine
{
public:
    engine_sdl()
        : engine()
    {
    }

    bool init() override;

    bool run() override;

private:
    void process_event(const SDL_KeyboardEvent& event);

    SDL_Window* window_ = nullptr;
};

} // namespace pt