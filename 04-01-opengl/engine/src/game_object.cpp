#include "game_object.hpp"

#include "engine.hpp"
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <LinearMath/btDefaultMotionState.h>
#include <game_object.hpp>

namespace pt
{

engine& game_object::get_engine()
{
    return *engine_;
}

game_object* game_object::set_position(const ptm::vec3& position)
{
    transformation_.position = position;
    return this;
}

const model& game_object::get_model() const
{
    return model_;
}

void game_object::set_model(const model& model, bool is_dynamic)
{
    has_model_ = true;
    model_     = model;
}

const transformation& game_object::get_transformation() const
{
    return transformation_;
}

void game_object::set_transform(const transformation& transform)
{
    transformation_ = transform;
}

void game_object::set_rotation(const ptm::vec3& rotation_vector, float angle)
{
    transformation_.rotation_vector = rotation_vector;
    transformation_.rotation_angle  = angle;

    if (body != nullptr)
    {
        btQuaternion rot{
            { rotation_vector.x, rotation_vector.y, rotation_vector.z }, angle
        };

        body->getWorldTransform().setRotation(rot);
    }
}

ptm::vec3 game_object::get_position() const
{
    return transformation_.position;
}

game_object* game_object::load_model(const std::string& path)
{
    set_model(model(path));
    return this;
}

game_object::~game_object()
{
    engine_ = nullptr;
}

game_object* game_object::set_scale(const ptm::vec3& scale)
{
    transformation_.scale = scale;

    if (body != nullptr)
    {
        body->getCollisionShape()->setLocalScaling(
            { scale.x, scale.y, scale.z });
    }

    return this;
}

ptm::vec3 game_object::get_scale() const
{
    return transformation_.scale;
}

game_object* game_object::add_body(bool is_dynamic)
{
    btCollisionShape* shape = new btBoxShape(
        { 0.5f * get_scale().x, 0.5f * get_scale().y, 0.5f * get_scale().z });

    btTransform bt_transform;
    bt_transform.setIdentity();

    bt_transform.setOrigin(
        { get_position().x, get_position().y, get_position().z });

    btScalar  mass(0.f);
    btVector3 localInertia(0, 0, 0);

    if (is_dynamic)
    {
        mass = 1.0f;
        // shape->calculateLocalInertia(mass, localInertia);
    }

    btDefaultMotionState* myMotionState =
        new btDefaultMotionState(bt_transform);

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape,
                                                    localInertia);

    body = new btRigidBody(rbInfo);

    get_engine().get_dynamics_world()->addRigidBody(body);

    return this;
}

} // namespace pt