#pragma once

#include <game_object.hpp>
#include <log_utils.hpp>
#include <ptm/math.hpp>

class enemy : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override;

    void update() override;

    void hit();


private:
    int health = 10;
    float move_speed = 1.f;

    class player* player_ = nullptr;
};