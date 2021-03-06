#pragma once

#include "enemy.hpp"
#include <game_object.hpp>
#include <time.h>

class enemies_spawner final : public pt::game_object
{
public:
    void kill_enemy()
    {
        total_enemies_--;
    }

private:
    using pt::game_object::game_object;

    void start() override { std::srand(time(nullptr)); }

    void update() override { spawn_enemy(); }

    void spawn_enemy()
    {
        last_spawn_time_ += get_engine().delta_time();

        if (last_spawn_time_ >= spawn_interval_ && total_enemies_ < 10)
        {
            const float x = std::rand() % 50;
            const float z = std::rand() % 50;
            const float y = 0.f;

            auto enemy_object = get_engine().add_object<enemy>(
                "Enemy " + std::to_string(enemies_counter_++));

            enemy_object->set_position({ x, y, z })->add_body(true);

            last_spawn_time_ = 0;

            total_enemies_++;
        }
    }



    float        spawn_interval_  = 1.0f; // seconds;
    float        last_spawn_time_ = 0.f;
    unsigned int enemies_counter_ = 1;
    unsigned int total_enemies_ = 0;
};
