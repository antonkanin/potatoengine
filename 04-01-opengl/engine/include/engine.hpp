#pragma once

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h> // TODO find a way to remove the bullet physics header
#include <functional>
#include <memory>
#include <ptm/vec2.hpp>
#include <ptm/vec3.hpp>

#define REGISTER(e, v) engine->register_class(#v, pt::make_object<v>);

namespace pt
{

class game_object;
class movable_object;
class input_manager;

class engine
{
public:
    using make_object_func =
        std::function<game_object*(engine&, std::string_view)>;

    engine();

    ~engine();

    bool init_engine();

    bool run();

    game_object* add_object(std::unique_ptr<game_object> object);

    template <typename T>
    game_object* add_object(std::string_view name)
    {
        return add_object(std::make_unique<T>(std::string(name)));
    }

    input_manager& get_input_manager();

    void set_title(const std::string& title);

    /** time from the start of the game */
    float time() const;

    /** duration of the previous frame */
    float delta_time() const;

    movable_object& get_camera();

    movable_object& get_light();

    void enable_wireframe(bool state);

    void set_light_model(const class model& model);

    btDiscreteDynamicsWorld* get_dynamics_world();

    bool load_sound(const std::string& sound_name,
                    const std::string& file_path);

    bool play_sound(const std::string& sound_name) const;

    ptm::vec2i get_window_size() const;

    void draw_line(const ptm::vec3& from, const ptm::vec3& to);
    void draw_line(const ptm::vec3& from, const ptm::vec3& to,
                   const ptm::vec3& color);

    void         add_body(game_object* game_object, btRigidBody* rigid_body);
    game_object* find_game_object(btRigidBody* rigid_body);

    void enable_physics(bool state);
    bool is_physics_enabled() const;

    bool is_game_running() const;

    void register_class(std::string_view class_name, make_object_func);

    game_object* make_object(std::string_view class_name,
                             std::string_view object_name);

    const std::vector<const char*>& object_types() const;

    using game_object_list = std::vector<std::unique_ptr<game_object>>;
    using const_object_iterator = game_object_list::const_iterator;

    const_object_iterator begin() const;
    const_object_iterator end() const;

private:
    std::unique_ptr<class engine_pimpl> impl;
};

} // namespace pt