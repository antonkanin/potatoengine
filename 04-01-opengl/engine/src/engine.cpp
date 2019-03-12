#include "engine.hpp"
#include "game_object.hpp"
#include "input_component.hpp"
#include "model.hpp"
#include "renderer/debug_drawer.hpp"
#include "renderer/triangle.hpp"
#include <cstdlib>
#include <engine.hpp>
#include <memory>

#include "video_component.hpp"
#include <bullet/btBulletDynamicsCommon.h>

namespace pt
{

std::unique_ptr<engine> make_engine()
{
    std::unique_ptr<engine> result(new engine());
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
            video_component_->render_object(
                object->get_model(), object->get_transformation(), get_camera(),
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
    // init_physics();

    game_running_ = true;

    start_objects();

    time_          = 0.f;
    float old_time = 0.f;

    while (game_running_)
    {
        input_component_->poll_events(*input_manager_.get());

        old_time = time_;
        time_    = video_component_->get_ticks() / 1000;

        delta_time_ = time_ - old_time;

        //        update_physics();

        update_objects();

        render_objects();

        render_lights();

        gui_component_->prepare_gui_frame();

        render_objects_gui();

        gui_component_->render_gui_frame();

        video_component_->swap_buffers();

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

    debug_drawer* debug_drawer_;

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

    // bullet_engine.debug_drawer_ = new debug_drawer(renderer_);;
}

void engine::update_physics()
{
    bullet_engine.dynamicsWorld->stepSimulation(delta_time(), 10);
}

btDiscreteDynamicsWorld* engine::get_dynamics_world()
{
    return bullet_engine.dynamicsWorld;
}

bool engine::init_engine()
{
    init_physics();
    video_component_->init(game_title_);
    gui_component_->init(video_component_->get_window());

    // TODO add a proper init check
    return true;
}

void engine::enable_wireframe(bool state)
{
    video_component_->enable_wireframe(state);
}

engine::~engine()
{
    video_component_->clean_up();
}

void engine::render_lights()
{
    video_component_->render_light(light_model_, get_light().get_position(),
                                   get_camera());
}

} // namespace pt