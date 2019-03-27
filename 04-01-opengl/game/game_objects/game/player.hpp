#pragma once

#include "../utils.hpp"
#include "enemy.hpp"
#include <game_object.hpp>
#include <glm/vec4.hpp>
#include <log_utils.hpp>

class player : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void update() override
    {
        handle_mouse_input();

        get_engine().draw_line({ world_from_.x, world_from_.y, world_from_.z },
                               { world_to_.x, world_to_.y, world_to_.z },
                               ptm::vec3::white());

//        std::cout << world_from_.x << ' ' << world_from_.y << ' ' << world_from_.z << ' ' <<
//        world_to_.x << ' ' << world_to_.y << ' ' << world_to_.z << std::endl;
    }

    void handle_mouse_input()
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::mouse_left))
        {
            glm::vec4 ndc_from = { .0f, 0.f, 1.0f, 1.0 };
            glm::vec4 ndc_to   = { .0f, 0.f, -1.0f, 1.0 };

            auto [world_from, world_to] =
                get_world_ray(get_engine(), ndc_from, ndc_to);

            world_from_ = world_from;
            world_to_   = world_to;

            auto found_obj =
                find_collision(get_engine(), world_from_, world_to_);

            if (found_obj != nullptr)
            {
                pt::log_line("Found object: " + found_obj->get_name());

                auto found_enemy = dynamic_cast<enemy*>(found_obj);

                if (nullptr != found_enemy)
                {
                    found_enemy->hit();
                    pt::log_line("found enemy");
                }
                else
                {
                    pt::log_line("missed");
                }
            }
        }
    }

private:
    glm::vec4 world_from_;
    glm::vec4 world_to_;
};
