#pragma once

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

private:
    std::unique_ptr<class gui_component_pimpl> pimpl_;
};

} // namespace pt