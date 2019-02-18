#pragma once

#include "engine.hpp"
#include <SDL2/SDL.h>

namespace pt
{

class engine_sdl final : public engine
{
public:
    ~engine_sdl();

    bool init() override;

    bool run() override;

private:
    void process_event(const SDL_KeyboardEvent& event);

    SDL_Window* window_ = nullptr;
};

} // namespace pt