#include "physics_component.hpp"

#include "renderer/debug_drawer.hpp"

namespace pt
{

class physics_component_pimpl
{
public:
    btDefaultCollisionConfiguration*     collisionConfig;
    btCollisionDispatcher*               dispatcher;
    btBroadphaseInterface*               overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld*             dynamicsWorld;
};

physics_component::physics_component()
    : pimpl_(std::make_unique<physics_component_pimpl>())
{
}

bool physics_component::init()
{
    pimpl_->collisionConfig = new btDefaultCollisionConfiguration();

    pimpl_->dispatcher = new btCollisionDispatcher(pimpl_->collisionConfig);

    pimpl_->overlappingPairCache = new btDbvtBroadphase();

    pimpl_->solver = new btSequentialImpulseConstraintSolver();

    // clang-format off
    pimpl_->dynamicsWorld = new btDiscreteDynamicsWorld(
            pimpl_->dispatcher,
            pimpl_->overlappingPairCache,
            pimpl_->solver,
            pimpl_->collisionConfig);
    // clang-format on

    pimpl_->dynamicsWorld->setGravity(btVector3(0, -10, 0));

    // bullet_engine.debug_drawer_ = new debug_drawer(renderer_);;

    return false;
}

void physics_component::update_physics(float delta_time)
{
    pimpl_->dynamicsWorld->stepSimulation(delta_time, 10);
}

btDiscreteDynamicsWorld* physics_component::get_dynamics_world()
{
    return pimpl_->dynamicsWorld;
}

physics_component::~physics_component() = default;

} // namespace pt