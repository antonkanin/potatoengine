#pragma once

#include "engine.hpp"
#include "renderer/renderer.hpp"
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

    void poll_events();

    void clean_up();     // TODO I really need a better name for this method

    void render_object(const vector3d& position) override;

    SDL_Window* window_ = nullptr;

    bool game_running_ = false;

    std::unique_ptr<renderer> renderer_;
};

} // namespace pt