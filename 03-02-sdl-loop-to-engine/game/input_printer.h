#pragma once

#include <game_object.h>
#include <iostream>

class input_printer : public pt::game_object
{
public:
    explicit input_printer(pt::engine& engine)
        : pt::game_object(engine){};

    void update() override
    {
        using namespace pt;

        print_key_state(key_code::up, "Up");
        print_key_state(key_code::right, "Right");
        print_key_state(key_code::down, "Down");
        print_key_state(key_code::left, "Left");

        print_key_state(key_code::select, "Select");
        print_key_state(key_code::start, "Start");
        print_key_state(key_code::button_a, "Button A");
        print_key_state(key_code::button_b, "Button B");
    }

    void print_key_state(pt::key_code code, std::string_view key_name)
    {
        auto& input = get_engine().get_input_manager();

        if (input.get_key_down(code))
        {
            std::cout << key_name << " is pressed\n";
        }

        if (input.get_key_up(code))
        {
            std::cout << key_name << " is released\n";
        }
    }
};

std::unique_ptr<pt::game_object> make_input_printer(pt::engine& engine)
{
    std::unique_ptr<pt::game_object> result(new input_printer(engine));
    return result;
}
