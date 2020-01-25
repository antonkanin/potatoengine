#pragma once

#include <SDL2/SDL_events.h>
#include <functional>
#include <memory>

namespace pt
{

class input_component
{
public:
    explicit input_component();

    ~input_component();

    bool init();

    void poll_events(class input_manager&                        input_manager,
                     std::function<void(const SDL_Event& event)> gui_callback,
                     std::function<void(const Sint32 x, const Sint32 y)>
                           screen_resize_callback,
                     bool& is_game_running);

private:
    std::unique_ptr<class input_component_pimpl> pimpl_;
};

} // namespace pt
