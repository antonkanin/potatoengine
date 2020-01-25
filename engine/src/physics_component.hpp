#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include <memory>

namespace pt
{

class physics_component
{
public:
    physics_component();

    ~physics_component();

    bool init();

    void update_physics(float delta_time);

    btDiscreteDynamicsWorld* get_dynamics_world();

private:
    std::unique_ptr<class physics_component_pimpl> pimpl_;
};

} // namespace pt