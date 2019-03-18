#include "input_component.hpp"

#include "engine_utils.hpp"
#include "input_manager.hpp"
#include "log_utils.hpp"
#include <SDL2/SDL.h>

namespace pt
{

class input_component_pimpl
{
public:
    void process_keyboard_event(const SDL_KeyboardEvent& event,
                                input_manager&           input_manager);

    void process_mouse_button_event(const SDL_MouseButtonEvent& event,
                                    input_manager&              input_manager);

    void process_mouse_motion_event(const SDL_MouseMotionEvent& event,
                                    input_manager&              input_manager);
};

input_component::input_component()
    : pimpl_(std::make_unique<input_component_pimpl>())
{
}

bool input_component::init()
{
    if (SDL_WasInit(SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("SDL Events already initialized\n");
        return true;
    }

    const int init_result = SDL_InitSubSystem(SDL_INIT_EVENTS);
    if (init_result != 0)
    {
        SDL_Log("Error: failed to initialize SDL Events %s", SDL_GetError());
        return false;
    }

    return true;
}

void input_component::poll_events(
    class input_manager&                                input_manager,
    std::function<void(const SDL_Event& event)>         gui_callback,
    std::function<void(const Sint32 x, const Sint32 y)> screen_resize_callback,
    bool&                                               is_game_running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        gui_callback(event);

        switch (event.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                pimpl_->process_keyboard_event(event.key, input_manager);
                break;
            }

            case SDL_QUIT:
            {
                is_game_running = false;
                break;
            }

            case SDL_MOUSEMOTION:
            {
                pimpl_->process_mouse_motion_event(event.motion, input_manager);
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                pimpl_->process_mouse_button_event(event.button, input_manager);
                break;
            }

            case SDL_WINDOWEVENT:
            {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    screen_resize_callback(event.window.data1, event.window.data2);
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }

    // process keyboard state
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);

    input_manager.key_code_state(key_code::left, key_state::pressed) =
        keystates[SDL_SCANCODE_K];

    input_manager.key_code_state(key_code::right, key_state::pressed) =
        keystates[SDL_SCANCODE_SEMICOLON];

    input_manager.key_code_state(key_code::up, key_state::pressed) =
        keystates[SDL_SCANCODE_O];

    input_manager.key_code_state(key_code::down, key_state::pressed) =
        keystates[SDL_SCANCODE_L];
}

input_component::~input_component() = default;

void input_component_pimpl::process_keyboard_event(
    const SDL_KeyboardEvent& event, input_manager& input_manager)
{
    auto code = get_key(event.keysym.sym);

    if (code == key_code::unsupported)
    {
        return;
    }

    input_manager.key_code_state(code, key_state::pressed) =
        (event.state == SDL_PRESSED);

    input_manager.key_code_state(code, key_state::released) =
        (event.state == SDL_RELEASED);
}

void input_component_pimpl::process_mouse_button_event(
    const SDL_MouseButtonEvent& event, input_manager& input_manager)
{
    if (event.button == SDL_BUTTON_LEFT)
    {
        input_manager.key_code_state(key_code::mouse_left, key_state::pressed) =
            (event.state == SDL_PRESSED);

        input_manager.key_code_state(key_code::mouse_left,
                                     key_state::released) =
            (event.state == SDL_RELEASED);
    }

    if (event.button == SDL_BUTTON_RIGHT)
    {
        input_manager.key_code_state(key_code::mouse_right,
                                     key_state::pressed) =
            (event.state == SDL_PRESSED);

        input_manager.key_code_state(key_code::mouse_right,
                                     key_state::released) =
            (event.state == SDL_RELEASED);
    }
}

void input_component_pimpl::process_mouse_motion_event(
    const SDL_MouseMotionEvent& event, input_manager& input_manager)
{
    input_manager.set_axis_x(event.xrel);
    input_manager.set_axis_y(event.yrel);
}

} // namespace pt