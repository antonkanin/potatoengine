#pragma once

#include <game_object.hpp>
#include <log_utils.hpp>
#include <ptm/math.hpp>

class enemy : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override;

    void update() override
    {
        // move_enemy();
    }

    void hit();

    void move_enemy();

private:
    int   health     = 2;
    float move_speed = 1.f;

    class player* player_ = nullptr;
};