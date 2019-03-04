#pragma once

#include <engine.hpp>
#include <game_object.hpp>
#include <key_code.hpp>

class camera_controller : public pt::game_object
{
public:
    camera_controller(pt::engine& engine)
        : pt::game_object(engine)
    {
    }

    void update() override { handle_camera_movement(); }

    void handle_camera_movement()
    {
        using namespace pt;

        const auto& input = get_engine().get_input_manager();
        const auto& trans = get_transformation();

        const float MOVEMENT_SPEED = 0.1f;

        if (input.get_key_down(key_code::right))
        {
            get_engine().get_camera().move_right(MOVEMENT_SPEED);
        }

        if (input.get_key_down(key_code::left))
        {
            get_engine().get_camera().move_left(MOVEMENT_SPEED);
        }

        if (input.get_key_down(key_code::up))
        {
            get_engine().get_camera().move_forward(MOVEMENT_SPEED);
        }

        if (input.get_key_down(key_code::down))
        {
            get_engine().get_camera().move_backward(MOVEMENT_SPEED);
        }

        if (input.get_key_down(key_code::jump))
        {
            get_engine().get_camera().move_up(MOVEMENT_SPEED);
        }

        if (input.get_key_down(key_code::crouch))
        {
            get_engine().get_camera().move_down(MOVEMENT_SPEED);
        }

        get_engine().get_camera().add_yaw(input.get_axis_x() * 0.02f);
        get_engine().get_camera().add_pitch(input.get_axis_y() * 0.02f);
    }
};