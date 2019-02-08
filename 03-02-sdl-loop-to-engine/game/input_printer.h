#pragma once

#include <game_object.h>
#include <iostream>

class input_printer : public pt::game_object
{
public:
    input_printer(pt::engine& engine)
        : pt::game_object(engine){};

    void update() override
    {
        if (get_engine().get_input_manager().get_key_down(pt::key_code::up))
        {
            std::cout << "Key up is pressed\n";
        }

        if (get_engine().get_input_manager().get_key_up(pt::key_code::up))
        {
            std::cout << "Key up is released\n";
        }
    }
};