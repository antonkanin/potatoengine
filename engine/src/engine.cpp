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

#include "game_objects_list.hpp"

namespace pt
{

class engine_impl
{
public:
    explicit engine_impl(engine* e)
        : engine_(e)
        , input_manager_(std::make_unique<input_manager>())
        , audio(std::make_unique<audio_component>())
        , input(std::make_unique<input_component>())
        , physics(std::make_unique<physics_component>())
        , gui(std::make_unique<gui_component>())
        , debug_drawer_(
              std::make_unique<debug_drawer>(video.get(), &camera_position_))
        , objects_(std::make_unique<game_objects_list>())

    {
        video = make_video_component(video_api_type::OPEN_GL);
    }

    engine* engine_;

    movable_object camera_position_;

    movable_object light_position_;

    std::unique_ptr<input_manager>     input_manager_;
    std::unique_ptr<audio_component>   audio;
    std::unique_ptr<input_component>   input;
    std::unique_ptr<video_component>   video;
    std::unique_ptr<physics_component> physics;
    std::unique_ptr<gui_component>     gui;

    std::map<std::string_view, engine::make_object_func> objects_register;

    std::vector<const char*> objects_types_;

    std::unique_ptr<debug_drawer> debug_drawer_;

    std::unique_ptr<model>
        light_model_; // TODO engine implementation needs to see this so it
    // can pass it to the renderer

    std::string game_title_;

    bool game_running_ = false;

    float time_       = 0.f;
    float delta_time_ = 0.f;

    std::unique_ptr<game_objects_list> objects_;

    // std::map<btRigidBody*, game_object*> body_objects_;

    bool physics_enabled_      = true;
    bool update_physics_state_ = false;
    bool new_physics_state_    = physics_enabled_;

    bool is_cursor_locked_ = false;

    void start_objects();

    void update_objects();

    void render_objects();

    void render_objects_gui();

    void render_lights();

    void render_cross_hairs();
};

engine::engine()
    : impl(std::make_unique<engine_impl>(this))
{
}

game_object* engine::add_object(std::unique_ptr<game_object> object)
{
    object->engine_ = this;

    // add object to the physics engine...

    game_object* object_ptr = object.get();
    impl->objects_->add_object(std::move(object));

    if (is_game_running())
    {
        object_ptr->start();
        log_line("Calling start()");
    }

    return object_ptr;
}

bool engine::run()
{
    impl->game_running_ = true;

    impl->start_objects();

    // load all the models

    impl->time_ = 0.f;

    while (impl->game_running_)
    {
        impl->input->poll_events(
            *(impl->input_manager_.get()), gui_component::gui_call_back,
            video_component::on_window_resize, impl->game_running_);

        float old_time = impl->time_;
        impl->time_    = impl->video->get_ticks() / 1000;

        impl->delta_time_ = impl->time_ - old_time;

        if (impl->physics_enabled_)
        {
            update_physics();
        }

        impl->update_objects();

        // impl->physics->get_dynamics_world()->debugDrawWorld();

        impl->render_objects();

        impl->render_lights();

        if (!cursor_locked())
        {
            impl->gui->prepare_gui_frame();

            impl->render_objects_gui();

            impl->gui->render_gui_frame();
        }

        impl->render_cross_hairs();

        impl->video->swap_buffers();

        get_input_manager().reset_states();

        // TODO test if we really need an updated physics...
        if (impl->update_physics_state_)
        {
            impl->update_physics_state_ = false;
            impl->physics_enabled_      = impl->new_physics_state_;
        }

        impl->objects_->clean_destoyed_objects();
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

void engine::set_light_model(const std::string& path)
{
    impl->light_model_ = std::move(load_model_from_file(path));

    load_model_into_gpu(impl->light_model_);
}

btDiscreteDynamicsWorld* engine::get_dynamics_world()
{
    return impl->physics->get_dynamics_world();
}

void engine::init_engine()
{
    impl->video->init(impl->game_title_);

    impl->gui->init(impl->video->get_window());

    impl->physics->init();

    impl->debug_drawer_->setDebugMode(btIDebugDraw::DBG_DrawWireframe);

    impl->physics->get_dynamics_world()->setDebugDrawer(
        impl->debug_drawer_.get());

    impl->audio->init();
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

game_object* engine::find_game_object(btRigidBody* rigid_body)
{
    return impl->objects_->find_object(rigid_body);
}

game_object* engine::find_game_object(std::string_view name)
{
    return impl->objects_->find_object(name);
}

void engine::add_body(game_object* game_object, btRigidBody* rigid_body)
{
    get_dynamics_world()->addRigidBody(rigid_body);

    game_object->body_ = rigid_body;
}

void engine::enable_physics(bool state)
{
    if (impl->physics_enabled_ != state)
    {
        impl->update_physics_state_ = true;
        impl->new_physics_state_    = state;
    }
    else
    {
        impl->update_physics_state_ = false;
    }
}

bool engine::is_physics_enabled() const
{
    return impl->physics_enabled_;
}

bool engine::is_game_running() const
{
    return impl->game_running_;
}

void engine::register_class(std::string_view class_name,
                            make_object_func make_function)
{
    if (impl->objects_register.count(class_name) > 0)
    {
        log_error(time(),
                  "Error: class already registered " + std::string(class_name));
        return;
    }

    impl->objects_register[class_name] = make_function;
    impl->objects_types_.push_back(class_name.data());
}

game_object* engine::make_object(std::string_view class_name,
                                 std::string_view object_name)
{
    if (impl->objects_register.count(class_name) <= 0)
    {
        log_error(time(), "cannot find type " + std::string(class_name));
        return nullptr;
    }

    make_object_func make_object = impl->objects_register[class_name];

    game_object* obj = make_object(*this, object_name);

    return obj;
}

const std::vector<const char*>& engine::object_types() const
{
    return impl->objects_types_;
}

engine::const_object_iterator engine::begin() const
{
    return impl->objects_->cbegin();
}

engine::const_object_iterator engine::end() const
{
    return impl->objects_->cend();
}

const char* const* engine::get_objects_names() const
{
    return impl->objects_->get_names();
}

game_objects_list& engine::objects()
{
    return *(impl->objects_.get());
}

void engine::cursor_locked(bool is_locked)
{
    impl->video->lock_cursor(is_locked);
    impl->is_cursor_locked_ = is_locked;
}

bool engine::cursor_locked() const
{
    return impl->is_cursor_locked_;
}

void engine::update_physics()
{
    impl->physics->update_physics(impl->delta_time_);
}

void engine::enable_vsync(bool state)
{
    impl->video->enable_vsync(state);
}

void engine::load_model_into_gpu(std::unique_ptr<model>& model_ptr)
{
    impl->video->load_model_into_gpu(model_ptr);
}

///////////////////////////////////////////////////////////////////////////////
// engine implementation

void engine_impl::update_objects()
{
    const auto size = objects_->size();
    for (size_t index = 0; index < size; ++index)
    {
        auto& object = (*objects_)[index];

        if (object.body_ != nullptr && physics_enabled_)
        {
            auto transform = object.body_->getWorldTransform();

            object.set_position_forced({ transform.getOrigin().x(),
                                         transform.getOrigin().y(),
                                         transform.getOrigin().z() });

            auto rot = transform.getRotation();

            object.set_rotation_forced(
                { rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z() },
                rot.getAngle());
        }

        object.update();
    }
}

void engine_impl::render_objects()
{
    for (auto& object : *objects_)
    {
        if (object->has_model_)
        {
            video->render_object(object->get_model(),
                                 object->get_transformation(),
                                 engine_->get_camera(),
                                 engine_->get_light().get_position(), time_);
        }
    }
}

void engine_impl::start_objects()
{
    for (auto& object : *objects_)
    {
        object->start();

        // check if the object has a model, and if it has one -> load it into
        // the GPU
    }
}

void engine_impl::render_objects_gui()
{
    const auto size = objects_->size();
    for (size_t index = 0; index < size; ++index)
    {
        (*objects_)[index].on_gui();
    }
}

void engine_impl::render_lights()
{
    if (nullptr != light_model_)
    {
        video->render_light(*light_model_, engine_->get_light().get_position(),
                            engine_->get_camera());
    }
}

void engine_impl::render_cross_hairs()
{
    const auto window_size = video->get_window_size();

    const float aspect_ratio =
        static_cast<float>(window_size.x) / static_cast<float>(window_size.y);

    const float cross_size = .4f / 2.f;

    video->render_line_ndc({ -cross_size, 0.f, 0.f }, { +cross_size, 0.f, 0.f },
                           { 1.f, 0.f, 0.f });

    video->render_line_ndc({ 0.f, -cross_size * aspect_ratio, 0.f },
                           { 0.f, +cross_size * aspect_ratio, 0.f },
                           { 1.f, 0.f, 0.f });
}

} // namespace pt