#pragma once

#include "../utils.hpp"
#include "enemy.hpp"
#include <game_object.hpp>
#include <glm/vec4.hpp>
#include <input_manager.hpp>
#include <log_utils.hpp>
#include <movable_object.hpp>

class player : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void update() override
    {
        handle_mouse_input();

        set_position(get_engine().get_camera().get_position());
    }

    void handle_mouse_input()
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::mouse_left))
        {
            glm::vec4 ndc_from = { .0f, 0.f, -1.0f, 1.0 };
            glm::vec4 ndc_to   = { .0f, 0.f, 1.0f, 1.0 };

            auto [world_from, world_to] =
                get_world_ray(get_engine(), ndc_from, ndc_to);

            auto found_obj = find_collision(get_engine(), world_from, world_to);

            if (found_obj != nullptr)
            {
                auto found_enemy = dynamic_cast<enemy*>(found_obj);

                if (nullptr != found_enemy)
                {
                    found_enemy->hit();
                }
                else
                {
                    pt::log_line("missed");
                }
            }
        }
    }
};
