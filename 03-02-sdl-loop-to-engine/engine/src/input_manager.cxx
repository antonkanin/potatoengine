#include "input_manager.h"
#include <input_manager.h>
#include <iostream>

namespace pt
{

input_manager::input_manager()
{
    std::cout << "input_manager() ctor" << std::endl;
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

bool& input_manager::key_code_state(const key_code& code, const key_state state)
{
    return keys_.at(code).at(state);
}

void input_manager::reset_states()
{
    // TODO need to refactor key_code into the container (possibly std::array?)
    // instead of using enum so we can integrate though values instead of
    // hardcoding them here

    keys_[key_code::up][key_state::pressed]  = false;
    keys_[key_code::up][key_state::released] = false;

    keys_[key_code::right][key_state::pressed]  = false;
    keys_[key_code::right][key_state::released] = false;

    keys_[key_code::down][key_state::pressed]  = false;
    keys_[key_code::down][key_state::released] = false;

    keys_[key_code::left][key_state::pressed]  = false;
    keys_[key_code::left][key_state::released] = false;

    keys_[key_code::button_a][key_state::pressed]  = false;
    keys_[key_code::button_a][key_state::released] = false;

    keys_[key_code::button_b][key_state::pressed]  = false;
    keys_[key_code::button_b][key_state::released] = false;

    keys_[key_code::select][key_state::pressed]  = false;
    keys_[key_code::select][key_state::released] = false;

    keys_[key_code::start][key_state::pressed]  = false;
    keys_[key_code::start][key_state::released] = false;
}

} // namespace pt