#include "engine.hpp"

#include "renderer/debug_drawer.hpp"

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <engine.hpp>
#include <log_utils.hpp>

#include "game_object.hpp"
#include "gui_component.hpp"
#include "input_component.hpp"
#include "physics_component.hpp"
#include "video_component.hpp"

#include "input_manager.hpp"
#include "movable_object.hpp"

namespace pt
{

std::unique_ptr<engine> make_engine()
{
    return std::make_unique<engine>();
}

class engine_pimpl
{
public:
    engine_pimpl()
        : input_manager_(std::make_unique<input_manager>())
        , gui(std::make_unique<gui_component>())
        , input(std::make_unique<input_component>())
        , video(std::make_unique<video_component>())
        , physics(std::make_unique<physics_component>())
    {
    }

    model light_model_; // TODO engine implementation needs to see this so it
    // can pass it to the renderer

    std::string game_title_;

    bool game_running_ = false;

    float time_       = 0.f;
    float delta_time_ = 0.f;

    movable_object camera_position_;

    movable_object light_position_;

    std::vector<std::unique_ptr<game_object>> objects_;

    std::unique_ptr<input_manager>     input_manager_;
    std::unique_ptr<input_component>   input;
    std::unique_ptr<video_component>   video;
    std::unique_ptr<gui_component>     gui;
    std::unique_ptr<physics_component> physics;
};

engine::engine()
    : impl(std::make_unique<engine_pimpl>())
{
}

game_object* engine::add_object(std::unique_ptr<game_object> object)
{
    object->engine_ = this;

    // add object to the physics engine...

    game_object* object_ptr = object.get();
    impl->objects_.emplace_back(std::move(object));
    return object_ptr;
}

void engine::update_objects()
{
    for (auto& object : impl->objects_)
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
    return *(impl->input_manager_);
}

void engine::render_objects()
{
    for (auto& object : impl->objects_)
    {
        if (object->has_model_)
        {
            impl->video->render_object(
                object->get_model(), object->get_transformation(), get_camera(),
                get_light().get_position());
        }
    }
}

void engine::set_title(const std::string& title)
{
    impl->game_title_ = title;
}

void engine::start_objects()
{
    for (auto& object : impl->objects_)
    {
        object->start();
    }
}

bool engine::run()
{
    impl->game_running_ = true;

    start_objects();

    impl->time_    = 0.f;
    float old_time = 0.f;

    while (impl->game_running_)
    {
        impl->input->poll_events(*impl->input_manager_.get());

        old_time    = impl->time_;
        impl->time_ = impl->video->get_ticks() / 1000;

        impl->delta_time_ = impl->time_ - old_time;

        //update_physics();
        impl->physics->update_physics(impl->delta_time_);

        update_objects();

        render_objects();

        render_lights();

        impl->gui->prepare_gui_frame();

        render_objects_gui();

        impl->gui->render_gui_frame();

        impl->video->swap_buffers();

        // TODO should this be moved to the engine implementation?
        get_input_manager().reset_states();
    }

    return true;
}

void engine::set_game_running(const bool is_game_running)
{
    impl->game_running_ = is_game_running;
}

float engine::time() const
{
    return impl->time_;
}

float engine::delta_time() const
{
    return impl->delta_time_;
}

void engine::render_objects_gui()
{
    for (auto& object : impl->objects_)
    {
        object->on_gui();
    }
}

void engine::set_light_model(const model& model)
{
    impl->light_model_ = model;
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
    // log_line(std::to_string(delta_time()));
    bullet_engine.dynamicsWorld->stepSimulation(delta_time(), 10);
}

btDiscreteDynamicsWorld* engine::get_dynamics_world()
{
    return impl->physics->get_dynamics_world();
}

bool engine::init_engine()
{
    //init_physics();

    impl->video->init(impl->game_title_);

    impl->gui->init(impl->video->get_window());

    impl->physics->init();

    // TODO add a proper init check
    return true;
}

void engine::enable_wireframe(bool state)
{
    impl->video->enable_wireframe(state);
}

engine::~engine()
{
    impl->video->clean_up();
}

void engine::render_lights()
{
    impl->video->render_light(impl->light_model_, get_light().get_position(),
                              get_camera());
}

movable_object& engine::get_camera()
{
    return impl->camera_position_;
}

movable_object& engine::get_light()
{
    return impl->light_position_;
}

} // namespace pt