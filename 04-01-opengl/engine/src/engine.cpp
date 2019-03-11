#include "engine.hpp"
#include "engine_sdl.hpp"
#include "game_object.hpp"
#include "model.hpp"
#include "renderer/triangle.hpp"
#include <cstdlib>
#include <engine.hpp>
#include <memory>

#include <bullet/btBulletDynamicsCommon.h>

namespace pt
{

std::unique_ptr<engine> make_engine()
{
    std::unique_ptr<engine> result(new engine_sdl());
    return result;
}

game_object* engine::add_object(std::unique_ptr<game_object> object)
{
    object->engine_ = this;

    // add object to the physics engine...

    game_object* object_ptr = object.get();
    objects_.emplace_back(std::move(object));
    return object_ptr;
}

void engine::update_objects()
{
    for (auto& object : objects_)
    {
        if (object->body != nullptr)
        {
            btTransform transform;
            object->body->getMotionState()->getWorldTransform(transform);

            object->set_position({ transform.getOrigin().x(),
                                   transform.getOrigin().y(),
                                   transform.getOrigin().z() });

            auto rot = transform.getRotation();

            object->set_rotation(
                { rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z() },
                rot.getAngle());

            std::cout << object->get_position() << '\n';
        }
        object->update();
    }
}

input_manager& engine::get_input_manager()
{
    return *input_manager_;
}

void engine::render_objects()
{
    for (auto& object : objects_)
    {
        if (object->has_model_)
        {
            render_object(object->get_model(), object->get_transformation(),
                          get_light().get_position());
        }
    }
}

void engine::set_title(const std::string& title)
{
    game_title_ = title;
}

void engine::start_objects()
{
    for (auto& object : objects_)
    {
        object->start();
    }
}

bool engine::run()
{
    //init_physics();

    game_running_ = true;

    start_objects();

    time_          = 0.f;
    float old_time = 0.f;

    while (game_running_)
    {
        poll_events();

        old_time = time_;
        time_    = get_ticks() / 1000;

        delta_time_ = time_ - old_time;

        update_physics();

        update_objects();

        render_objects();

        render_lights();

        // GUI rendering
        prepare_gui_frame();

        render_objects_gui();

        render_gui_frame();

        // swap buffers
        post_render_objects();

        // TODO should this be moved to the engine implementation?
        get_input_manager().reset_states();
    }

    return true;
}

void engine::set_game_running(const bool is_game_running)
{
    game_running_ = is_game_running;
}

float engine::time() const
{
    return time_;
}

float engine::delta_time() const
{
    return delta_time_;
}

void engine::render_objects_gui()
{
    for (auto& object : objects_)
    {
        object->on_gui();
    }
}

void engine::set_light_model(const model& model)
{
    light_model_ = model;
}

struct bullet_config
{
    btDefaultCollisionConfiguration*     collisionConfig;
    btCollisionDispatcher*               dispatcher;
    btBroadphaseInterface*               overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld*             dynamicsWorld;
} bullet_engine;

void engine::init_physics()
{
    bullet_engine.collisionConfig = new btDefaultCollisionConfiguration();

    bullet_engine.dispatcher =
        new btCollisionDispatcher(bullet_engine.collisionConfig);

    bullet_engine.overlappingPairCache = new btDbvtBroadphase();

    bullet_engine.solver = new btSequentialImpulseConstraintSolver();

    // clang-format off
    bullet_engine.dynamicsWorld = new btDiscreteDynamicsWorld(
        bullet_engine.dispatcher,
        bullet_engine.overlappingPairCache,
        bullet_engine.solver,
        bullet_engine.collisionConfig);
    // clang-format on

    bullet_engine.dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void engine::update_physics()
{
    bullet_engine.dynamicsWorld->stepSimulation(delta_time(), 10);
}

btDiscreteDynamicsWorld* engine::get_dynamics_world()
{
    return bullet_engine.dynamicsWorld;
}

} // namespace pt