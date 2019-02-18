#pragma once

#include "vector3d.hpp"

namespace pt
{

class engine;

class game_object
{
public:
    game_object(engine& engine)
        : engine_(engine)
    {
    }

    virtual ~game_object() = default;

    virtual void update() = 0;

    vector3d get_position() const;
    void set_position(const vector3d& position);

protected:
    engine& get_engine();

private:
    pt::engine& engine_;

    vector3d position_ = {0.0, 0.0, 0.0};
};

} // namespace pt