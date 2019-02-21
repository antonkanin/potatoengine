#pragma once

#include "vector3d.hpp"

namespace pt
{

class engine;

class game_object
{
public:
    explicit game_object(engine& engine)
        : engine_(engine)
    {
    }

    virtual ~game_object() = default;

    /** called once for each game object before the main loop */
    virtual void start(){};

    /** called every frame */
    virtual void update() = 0;

    vector3d get_position() const;
    void     set_position(const vector3d& position);

    vector3d get_rotation() const;
    void set_roration(const vector3d& rotation);

protected:
    engine& get_engine();

private:
    friend engine;

    engine& engine_;

    vector3d position_ = { 0.0, 0.0, 0.0 };
    vector3d rotation_ = { 0.0, 0.0, 0.0 };
};

} // namespace pt