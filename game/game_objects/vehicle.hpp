#pragma once

#include <game_object.hpp>

class vehicle final : public pt::game_object
{
    using pt::game_object::game_object;

    void start() override { load_model("res/military_vehicle_2.obj"); }

    void update() override {}
};
