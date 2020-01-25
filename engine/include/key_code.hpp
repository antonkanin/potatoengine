#pragma once

namespace pt
{

enum class key_code
{
    unsupported = 0,
    up          = 1,
    right       = 2,
    down        = 3,
    left        = 4,
    button_a    = 5,
    button_b    = 6,
    select      = 7,
    start       = 8,
    jump        = 9,
    crouch      = 10,

    mouse_left  = 11,
    mouse_right = 12,

    F12 = 13
};

enum class key_state
{
    pressed  = 0,
    released = 1
};

} // namespace pt