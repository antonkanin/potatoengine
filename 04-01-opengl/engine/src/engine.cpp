#include <engine.hpp>
#include <log_utils.hpp>

#include "audio_component.hpp"
#include "game_object.hpp"
#include "gui_component.hpp"
#include "input_component.hpp"
#include "physics_component.hpp"
#include "video_component.hpp"

#include "input_manager.hpp"
#include "movable_object.hpp"
#include "renderer/debug_drawer.hpp"

namespace pt
{

class engine_pimpl
{
public:
    explicit engine_pimpl(engine* e)
        : engine_(e)
        , input_manager_(std::make_unique<input_manager>())
        , audio(std::make_unique<audio_component>())
        , gui(std::make_unique<gui_component>())
        , input(std::make_unique<input_component>())
        , video(std::make_unique<video_component>())
        , physics(std::make_unique<physics_component>())
    {
    }

    engine* engine_;

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
    std::unique_ptr<audio_component>   audio;

    debug_drawer* debug_drawer_;

    void start_objects();

    void update_objects();

    void render_objects();

    void render_objects_gui();

    void render_lights();
};

engine::engine()
    : impl(std::make_unique<engine_pimpl>(this))
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

bool engine::run()
{
    impl->game_running_ = true;

    impl->start_objects();

    impl->time_    = 0.f;
    float old_time = 0.f;

    while (impl->game_running_)
    {
        impl->input->poll_events(*impl->input_manager_.get(),
                                 gui_component::gui_call_back,
                                 impl->game_running_);

        old_time    = impl->time_;
        impl->time_ = impl->video->get_ticks() / 1000;

        impl->delta_time_ = impl->time_ - old_time;

        impl->physics->update_physics(impl->delta_time_);

        impl->update_objects();

        impl->render_objects();

        impl->render_lights();

        impl->physics->get_dynamics_world()->debugDrawWorld();

        impl->gui->prepare_gui_frame();

        impl->render_objects_gui();

        impl->gui->render_gui_frame();

        impl->video->swap_buffers();

        get_input_manager().reset_states();
    }

    return true;
}

float engine::time() const
{
    return impl->time_;
}

float engine::delta_time() const
{
    return impl->delta_time_;
}

void engine::set_light_model(const model& model)
{
    impl->light_model_ = model;
}

btDiscreteDynamicsWorld* engine::get_dynamics_world()
{
    return impl->physics->get_dynamics_world();
}

bool engine::init_engine()
{
    impl->video->init(impl->game_title_);

    impl->gui->init(impl->video->get_window());

    impl->physics->init();

    impl->debug_drawer_ = new debug_drawer(impl->video.get(), &get_camera());
    impl->debug_drawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);

    impl->physics->get_dynamics_world()->setDebugDrawer(impl->debug_drawer_);

    impl->audio->init();

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

movable_object& engine::get_camera()
{
    return impl->camera_position_;
}

movable_object& engine::get_light()
{
    return impl->light_position_;
}

void engine::set_title(const std::string& title)
{
    impl->game_title_ = title;
}

input_manager& engine::get_input_manager()
{
    return *(impl->input_manager_);
}

bool engine::load_sound(const std::string& sound_name,
                        const std::string& file_path)
{
    return impl->audio->load_sound(sound_name, file_path);
}

bool engine::play_sound(const std::string& sound_name) const
{
    return impl->audio->play_sound(sound_name);
}

ptm::vec2i engine::get_window_size() const
{
    return impl->video->get_window_size();
}

void engine::draw_line(const ptm::vec3& from, const ptm::vec3& to,
                       const ptm::vec3& color)
{
    impl->video->render_line(from, to, color, get_camera());
}

void engine::draw_line(const ptm::vec3& from, const ptm::vec3& to)
{
    draw_line(from, to, { 1.f, 0.f, 0.f });
}

///////////////////////////////////////////////////////////////////////////////
// engine implementation

void engine_pimpl::update_objects()
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

void engine_pimpl::render_objects()
{
    for (auto& object : objects_)
    {
        if (object->has_model_)
        {
            video->render_object(
                object->get_model(), object->get_transformation(),
                engine_->get_camera(), engine_->get_light().get_position());
        }
    }
}

void engine_pimpl::start_objects()
{
    for (auto& object : objects_)
    {
        object->start();
    }
}

void engine_pimpl::render_objects_gui()
{
    for (auto& object : objects_)
    {
        object->on_gui();
    }
}

void engine_pimpl::render_lights()
{
    video->render_light(light_model_, engine_->get_light().get_position(),
                        engine_->get_camera());
}

} // namespace pt