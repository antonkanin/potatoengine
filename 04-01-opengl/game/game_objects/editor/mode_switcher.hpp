#pragma once

#include <game_object.hpp>
#include <input_manager.hpp>

class mode_switcher : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void update() override
    {
        if (get_engine().get_input_manager().get_key_down(pt::key_code::F12))
        {
            get_engine().cursor_locked(!get_engine().cursor_locked());
        }
    }
};
