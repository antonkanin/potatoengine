#pragma once

#include <map>
#include "key_code.h"

namespace pt
{

class engine;

class input_manager
{
public:
    input_manager();

    bool get_key_down(const key_code& key_code) const;

    bool get_key_up(const key_code& key_code) const;

    bool& key_code_state(const key_code& code, const key_state state);

    void reset_states();


private:
    std::map<key_code, std::map<key_state, bool>> keys_;
};

} // namespace pt