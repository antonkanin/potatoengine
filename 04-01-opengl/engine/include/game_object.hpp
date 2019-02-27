#pragma once

#include "model.hpp"
#include "transformation.hpp"
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

    void set_transform(const transformation& transform);

    const transformation& get_transformation() const;

    void set_position(const vector3d& position);

    void set_rotation(const vector3d& rotation_vector, float angle);

    const model& get_model() const;
    void         set_model(const model& model);

protected:
    engine& get_engine();

private:
    friend engine;

    engine& engine_;

    model model_;

    transformation transformation_ = { zero_vector, up_vector, 0.0f,
                                       zero_vector };
};

} // namespace pt