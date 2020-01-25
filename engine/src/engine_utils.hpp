#pragma once

#include "key_code.hpp"
#include <SDL2/SDL_events.h>

namespace pt
{

key_code get_key(const SDL_Keycode& sdl_keycode);

} // namespace pt