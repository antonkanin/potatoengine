#include "input_manager.hpp"
#include <iostream>

#include "log_utils.hpp"
namespace pt
{

input_manager::input_manager()
{
    log_line("Input manager ctor");
    reset_states();
}

bool input_manager::get_key_down(const key_code& key_code) const
{
    return keys_.at(key_code).at(key_state::pressed);
}

bool input_manager::get_key_up(const key_code& key_code) const
{
    return keys_.at(key_code).at(key_state::released);
}

bool& input_manager::key_code_state(const key_code&  code,
                                    const key_state& state)
{
    return keys_.at(code).at(state);
}

void input_manager::reset_key_state(key_code code)
{
    keys_[code][key_state::pressed]  = false;
    keys_[code][key_state::released] = false;
}

void input_manager::reset_states()
{
    // TODO need to refactor key_code into the container (possibly std::array?)
    // instead of using enum so we can integrate though values instead of
    // hardcoding them here

    reset_key_state(key_code::up);
    reset_key_state(key_code::right);
    reset_key_state(key_code::left);
    reset_key_state(key_code::down);
    reset_key_state(key_code::button_a);
    reset_key_state(key_code::button_b);
    reset_key_state(key_code::select);
    reset_key_state(key_code::start);
    reset_key_state(key_code::jump);
    reset_key_state(key_code::crouch);

    reset_key_state(key_code::mouse_right);
    reset_key_state(key_code::mouse_left);

    axis_x_ = 0.f;
    axis_y_ = 0.f;
}

} // namespace pt