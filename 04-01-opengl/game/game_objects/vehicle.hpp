#pragma once

#include <engine.hpp>
#include <game_object.hpp>

class vehicle final : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override { load_model("res/military_vehicle_2.obj"); }

    void update() override {}
};