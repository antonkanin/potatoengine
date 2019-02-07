#pragma once

#include "engine.h"

namespace pt
{

class game_object
{
public:
    game_object(engine& engine) : engine_(engine)
    {
    }

    virtual ~game_object() = 0;

    virtual void update() = 0;

protected:
    const engine& engine() const;

private:
    pt::engine& engine_;
};

} // namespace pt