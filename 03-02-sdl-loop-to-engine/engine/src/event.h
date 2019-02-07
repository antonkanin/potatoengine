#pragma once

namespace pt
{

enum class KeyCode
{
    unsupported,
    up,
    right,
    down,
    left,
    button_a,
    button_b,
    select,
    start
};

enum class KeyState
{
    pressed,
    released
};

struct Event
{
    KeyCode  key;
    KeyState key_state;
};

} // namespace pt