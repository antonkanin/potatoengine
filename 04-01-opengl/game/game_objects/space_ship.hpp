#pragma once

#include <game_object.hpp>
#include <iostream>
#include <key_code.hpp>
#include <log_utils.hpp>
#include <ptm/vec3.hpp>
#include <vertex.hpp>

class space_ship final : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override
    {
        set_model(pt::model("res/cube/cube.obj"));
        // set_model(pt::model("res/figure.obj"));
        // set_model(pt::model("res/two_faces.obj"));
    }

    void update() override
    {
        process_movement();

        process_rotation();
    }

    void process_rotation()
    {
        if (is_auto_rotate_)
        {
            using namespace pt;
            set_rotation(up_vector, get_transformation().rotation_angle -
                                        get_engine().delta_time() * 0.3f);
        }
    }

    void process_movement()
    {
        using namespace pt;

        const auto& input = get_engine().get_input_manager();
        const auto& trans = get_transformation();

        if (input.get_key_down(key_code::button_a))
        {
            set_rotation(up_vector, trans.rotation_angle - 0.3f);
        }

        if (input.get_key_down(key_code::button_b))
        {
            set_rotation(up_vector, trans.rotation_angle + 0.3f);
        }

        if (input.get_key_down(key_code::start))
        {
            set_rotation(left_vector, trans.rotation_angle - 0.3f);
        }

        if (input.get_key_down(key_code::select))
        {
            set_rotation(left_vector, trans.rotation_angle + 0.3f);
        }
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

    void print_keys()
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

public:
    bool is_auto_rotate_ = true;
};