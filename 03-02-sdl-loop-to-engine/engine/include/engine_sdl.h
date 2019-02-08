#pragma once

#include <SDL2/SDL.h>
#include "engine.h"

namespace pt
{

class engine_sdl : public engine
{
public:
    engine_sdl() : engine() {}

    bool init() override;

    bool run() override;

private:
    void process_event(const SDL_KeyboardEvent& event);

    SDL_Window* window_;
};

} // namespace pt