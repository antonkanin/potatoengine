#pragma once

#include <game_object.hpp>
#include <engine.hpp>

class light final : public pt::game_object
{
public:
    void start() override
    {
        set_model(pt::model{"res/figure.obj"});
    }

    void update() override
    {

    }
};
