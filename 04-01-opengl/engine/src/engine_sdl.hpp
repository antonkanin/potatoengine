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

    //bool run() override;

    float time() const override;

    float delta_time() const override;

private:
    void post_render_objects() override;

    void process_event(const SDL_KeyboardEvent& event);

    void poll_events() override;

    void clean_up(); // TODO I really need a better name for this method

    void render_object(const model&          model,
                       const transformation& transformation) override;

    void load_models() override;

    SDL_Window* window_ = nullptr;

    std::unique_ptr<renderer> renderer_;
};

} // namespace pt