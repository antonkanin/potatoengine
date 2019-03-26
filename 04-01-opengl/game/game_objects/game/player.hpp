#pragma once

#include <game_object.hpp>
#include "enemy.hpp"
#include <log_utils.hpp>

class player : public pt::game_object
{
public:
    using pt::game_object::game_object;


    void handle_mouse_input()
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::mouse_left))
        {
            const auto [mouse_from, mouse_to] = get_mouse_ndc();

            auto found_obj = find_collision(get_engine(), mouse_from, mouse_to);

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


