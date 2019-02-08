#pragma once

#include "engine.h"

namespace pt
{

class game_object
{
public:
    game_object(engine& engine)
        : engine_(engine)
    {
    }

    virtual ~game_object(){};

    virtual void update() = 0;

protected:
    engine& get_engine();

private:
    pt::engine& engine_;
};

} // namespace pt