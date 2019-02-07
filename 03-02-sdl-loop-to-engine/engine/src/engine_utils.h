#pragma once

#include "engine.h"
#include "event.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

pt::KeyCode get_key(const SDL_Keycode& keycode)
{
    using namespace pt;

    switch (keycode)
    {
        case SDLK_UP:
        {
            return KeyCode::up;
        }

        case SDLK_RIGHT:
        {
            return KeyCode::right;
        }

        case SDLK_DOWN:
        {
            return KeyCode::down;
        }

        case SDLK_LEFT:
        {
            return KeyCode::left;
        }

        case SDLK_q:
        {
            return KeyCode::button_a;
        }

        case SDLK_w:
        {
            return KeyCode::button_b;
        }

        case SDLK_a:
        {
            return KeyCode::start;
        }

        case SDLK_s:
        {
            return KeyCode::select;
        }

        default:
        {
            return KeyCode::unsupported;
        }
    }
}

pt::KeyState get_keystate(const Uint8 state)
{
    using namespace pt;

    if (state == SDL_PRESSED)
    {
        return KeyState::pressed;
    }

    return KeyState::released;
}
