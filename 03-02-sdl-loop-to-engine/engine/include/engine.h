#pragma once

#include <memory>

namespace pt
{

enum class Key
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
    Key   key;
    KeyState key_state;
};

class engine
{
public:
    virtual bool init() = 0;

    virtual bool poll_events(Event& ev) = 0;

    virtual void process_input(const Event& ev) = 0;
};

std::unique_ptr<engine> make_engine();

} // namespace pt