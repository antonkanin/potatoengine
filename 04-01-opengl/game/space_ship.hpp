#pragma once

#include <game_object.hpp>
#include <iostream>
#include <key_code.hpp>
#include <read_obj.hpp>
#include <texture_image.hpp>
#include <ptm/vec3.hpp>
#include <vertex.hpp>

class space_ship final : public pt::game_object
{
public:
    explicit space_ship(pt::engine& engine)
        : pt::game_object(engine){};

    void start() override
    {
        auto cube_model = pt::read_obj("figure.obj");

        cube_model.image = pt::make_image("figure.png");

        set_model(cube_model);

        set_position(get_transformation().position +
                     pt::vec3{ 0.0f, 0.0f, -5.0f });
    }

    void update() override
    {
        //handle_movement();
        handle_camera_movement();

        handle_rotation();

        print_keys();
    }

    void handle_movement()
    {
        using namespace pt;

        const auto& input = get_engine().get_input_manager();
        const auto& trans = get_transformation();

        if (input.get_key_down(key_code::right))
        {
            set_position(trans.position + vec3{ 0.1f, 0, 0 });
        }

        if (input.get_key_down(key_code::left))
        {
            set_position(trans.position - vec3{ 0.1f, 0, 0 });
        }

        if (input.get_key_down(key_code::up))
        {
            set_position(trans.position + vec3{ 0, 0.1f, 0 });
        }

        if (input.get_key_down(key_code::down))
        {
            set_position(trans.position - vec3{ 0, 0.1f, 0 });
        }
    }

    void handle_rotation()
    {
        using namespace pt;

        const auto& input = get_engine().get_input_manager();
        const auto& trans = get_transformation();

        set_rotation(up_vector,
                     trans.rotation_angle - get_engine().delta_time() * 0.3f);

        if (input.get_key_down(key_code::button_a))
        {
            // set_rotation(trans.rotation_vector, trans.rotation_angle - 0.3f);
            set_rotation(up_vector, trans.rotation_angle - 0.3f);
        }

        if (input.get_key_down(key_code::button_b))
        {
            set_rotation(up_vector, trans.rotation_angle + 0.3f);
        }

        if (input.get_key_down(key_code::start))
        {
            // set_rotation(trans.rotation_vector, trans.rotation_angle - 0.3f);
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

    void handle_camera_movement()
    {
        using namespace pt;

        const auto& input = get_engine().get_input_manager();
        const auto& trans = get_transformation();

        if (input.get_key_down(key_code::right))
        {
            get_engine().get_camera().move_right(.1f);
        }

        if (input.get_key_down(key_code::left))
        {
            get_engine().get_camera().move_left(.1f);
        }

        if (input.get_key_down(key_code::up))
        {
            get_engine().get_camera().move_forward(.1f);
        }

        if (input.get_key_down(key_code::down))
        {
            get_engine().get_camera().move_backward(.1f);
        }

    }

};

std::unique_ptr<pt::game_object> make_space_ship(pt::engine& engine)
{
    std::unique_ptr<pt::game_object> result(new space_ship(engine));
    return result;
}
