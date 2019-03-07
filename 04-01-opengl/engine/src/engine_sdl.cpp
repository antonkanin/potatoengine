#include "engine_sdl.hpp"
#include "engine_utils.hpp"
#include "imgui/imgui_impl_sdl.h"
#include "log_utils.hpp"
#include "renderer/renderer.hpp"
#include "renderer/triangle.hpp"
#include <imgui.h>

namespace pt
{

bool engine_sdl::init()
{
    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
        return false;
    }

    const unsigned int WINDOW_WIDTH  = 1024;
    const unsigned int WINDOW_HEIGHT = 768;

    // TODO fix the warning "Warning:(47, 43) Clang-Tidy: Use of a signed
    // integer operand with a binary bitwise operator"
    window_ = SDL_CreateWindow(game_title_.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    if (window_ == nullptr)
    {
        SDL_Log("Error: failed to SDL window %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer_ = make_renderer();

    if (!renderer_->initialize(window_))
    {
        clean_up();
        return false;
    };

    // locking mouse at the center of the screen
    // SDL_SetRelativeMouseMode(SDL_TRUE);

    return true;
}

void engine_sdl::process_keyboard_event(const SDL_KeyboardEvent& event)
{
    auto code = get_key(event.keysym.sym);

    if (code == key_code::unsupported)
    {
        return;
    }

    get_input_manager().key_code_state(code, key_state::pressed) =
        (event.state == SDL_PRESSED);

    get_input_manager().key_code_state(code, key_state::released) =
        (event.state == SDL_RELEASED);
}

void engine_sdl::process_mouse_button_event(const SDL_MouseButtonEvent& event)
{
    if (event.button == SDL_BUTTON_LEFT)
    {
        get_input_manager().key_code_state(key_code::mouse_left,
                                           key_state::pressed) =
            (event.state == SDL_PRESSED);

        get_input_manager().key_code_state(key_code::mouse_left,
                                           key_state::released) =
            (event.state == SDL_RELEASED);
    }

    if (event.button == SDL_BUTTON_RIGHT)
    {
        get_input_manager().key_code_state(key_code::mouse_right,
                                           key_state::pressed) =
            (event.state == SDL_PRESSED);

        get_input_manager().key_code_state(key_code::mouse_right,
                                           key_state::released) =
            (event.state == SDL_RELEASED);
    }
}

engine_sdl::~engine_sdl()
{
    clean_up();
}

void engine_sdl::poll_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        switch (event.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                process_keyboard_event(event.key);
                break;
            }

            case SDL_QUIT:
            {
                set_game_running(false);
                break;
            }

            case SDL_MOUSEMOTION:
            {
                process_mouse_motion_event(event.motion);
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                process_mouse_button_event(event.button);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

void engine_sdl::clean_up()
{
    if (window_ != nullptr)
    {
        SDL_DestroyWindow(window_);
    }

    SDL_Quit();
}

void engine_sdl::render_object(const model&          model,
                               const transformation& transformation,
                               const ptm::vec3&      light_position)
{
    renderer_->render_model(model, transformation, get_camera(),
                            light_position);
}

void engine_sdl::post_render_objects()
{
    renderer_->swap_buffers();
}

float engine_sdl::get_ticks()
{
    return SDL_GetTicks();
}

void engine_sdl::process_mouse_motion_event(const SDL_MouseMotionEvent& event)
{
    get_input_manager().set_axis_x(event.xrel);
    get_input_manager().set_axis_y(event.yrel);
}

void engine_sdl::enable_vsync(bool state)
{
    renderer_->enable_vsync(state);
}

void engine_sdl::prepare_gui_frame()
{
    renderer_->prepare_gui_frame();
}

void engine_sdl::render_gui_frame()
{
    renderer_->render_gui_frame();
}

void engine_sdl::render_lights()
{
    renderer_->render_light(light_model_, get_light().get_position(),
                            get_camera());
}

} // namespace pt