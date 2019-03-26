#include "engine_utils.hpp"

pt::key_code pt::get_key(const SDL_Keycode& sdl_keycode)
{
    using namespace pt;

    switch (sdl_keycode)
    {
        case SDLK_o: // SDLK_UP:
        {
            return key_code::up;
        }

        case SDLK_SEMICOLON: // SDLK_RIGHT:
        {
            return key_code::right;
        }

        case SDLK_l: // SDLK_DOWN:
        {
            return key_code::down;
        }

        case SDLK_k: // SDLK_LEFT:
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

        case SDLK_SPACE:
        {
            return key_code::jump;
        }

        case SDLK_RSHIFT:
        {
            return key_code::crouch;
        }

        case SDLK_F12:
        {
            return key_code::F12;
        }

        default:
        {
            return key_code::unsupported;
        }
    }
}
