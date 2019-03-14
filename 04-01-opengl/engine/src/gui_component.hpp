#pragma once

#include <SDL2/SDL_events.h>
#include <memory>

class SDL_Window;

namespace pt
{

class gui_component
{
public:
    gui_component();

    ~gui_component();

    void init(SDL_Window* window);

    void prepare_gui_frame();

    void render_gui_frame();

    static void gui_call_back(const SDL_Event& event);

private:
    std::unique_ptr<class gui_component_pimpl> pimpl_;
};



} // namespace pt