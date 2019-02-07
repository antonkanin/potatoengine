#pragma once

#include "engine.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

pt::Key get_key(const SDL_Keycode& keycode)
{
    using namespace pt;

    switch (keycode)
    {
        case SDLK_UP:
        {
            return Key::up;
        }

        case SDLK_RIGHT:
        {
            return Key::right;
        }

        case SDLK_DOWN:
        {
            return Key::down;
        }

        case SDLK_LEFT:
        {
            return Key::left;
        }

        case SDLK_q:
        {
            return Key::button_a;
        }

        case SDLK_w:
        {
            return Key::button_b;
        }

        case SDLK_a:
        {
            return Key::start;
        }

        case SDLK_s:
        {
            return Key::select;
        }

        default:
        {
            return Key::unsupported;
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
