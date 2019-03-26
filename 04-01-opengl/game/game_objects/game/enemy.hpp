#pragma once

#include <game_object.hpp>
#include <log_utils.hpp>

class enemy : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void hit()
    {
        pt::log_line("My health " + std::to_string(health));
        health--;
    }

private:
    int health = 10;
};