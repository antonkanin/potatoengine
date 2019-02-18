#pragma once

#include <game_object.hpp>
#include <iostream>
#include <key_code.hpp>

class space_ship final : public pt::game_object
{
public:
    explicit space_ship(pt::engine& engine)
        : pt::game_object(engine){};

    void update() override
    {
        using namespace pt;

        move_object();

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

    void move_object()
    {
        using namespace pt;

        const auto& input = get_engine().get_input_manager();

        if (input.get_key_down(key_code::right))
        {
            set_position(get_position() + vector3d{ 0.1f, 0, 0 });
        }

        if (input.get_key_down(key_code::left))
        {
            set_position(get_position() - vector3d{ 0.1f, 0, 0 });
        }

        if (input.get_key_down(key_code::up))
        {
            set_position(get_position() + vector3d{ 0, 0.1f, 0 });
        }

        if (input.get_key_down(key_code::down))
        {
            set_position(get_position() - vector3d{ 0, 0.1f, 0 });
        }
    }
};

std::unique_ptr<pt::game_object> make_input_printer(pt::engine& engine)
{
    std::unique_ptr<pt::game_object> result(new space_ship(engine));
    return result;
}
