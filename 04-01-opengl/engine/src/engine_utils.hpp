#pragma once

#include "key_code.hpp"
#include "ptm/vec3.hpp"
#include "vertex.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

pt::key_code get_key(const SDL_Keycode& sdl_keycode)
{
    using namespace pt;

    switch (sdl_keycode)
    {
        case SDLK_UP:
        {
            return key_code::up;
        }

        case SDLK_RIGHT:
        {
            return key_code::right;
        }

        case SDLK_DOWN:
        {
            return key_code::down;
        }

        case SDLK_LEFT:
        {
            return key_code::left;
        }

        case SDLK_q:
        {
            return key_code::button_a;
        }

        case SDLK_w:
        {
            return key_code::button_b;
        }

        case SDLK_a:
        {
            return key_code::start;
        }

        case SDLK_s:
        {
            return key_code::select;
        }

        default:
        {
            return key_code::unsupported;
        }
    }
}

bool is_keycode_supported(const SDL_Keycode& sdl_keycode)
{
    return (sdl_keycode == SDLK_UP || sdl_keycode == SDLK_RIGHT ||
            sdl_keycode == SDLK_LEFT || sdl_keycode == SDLK_RIGHT ||
            sdl_keycode == SDLK_q || sdl_keycode == SDLK_w ||
            sdl_keycode == SDLK_a || sdl_keycode == SDLK_s);
}

pt::vertex world_to_screen(const pt::vec3& position)
{
    return { position.x, position.y, position.z };
}
