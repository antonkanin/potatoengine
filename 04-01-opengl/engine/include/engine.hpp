#pragma once

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <iostream>
#include <memory>
#include <vector>

// abstraction instead of including a private header

#include "input_manager.hpp"
#include "key_code.hpp"
#include "movable_object.hpp"
#include "transformation.hpp"

namespace pt
{

class game_object;

class engine
{
public:
    engine();
    ~engine();

    bool init_engine();

    bool run();

    game_object* add_object(std::unique_ptr<game_object> object);

    template <typename T>
    game_object* add_object()
    {
        return add_object(std::make_unique<T>());
    }

    input_manager& get_input_manager();

    void set_title(const std::string& title);

    /** time from the start of the game */
    float time() const;

    /** duration of the previous frame */
    float delta_time() const;

    movable_object& get_camera() { return camera_position_; }

    movable_object& get_light() { return light_position_; }

    void enable_wireframe(bool state);

    void set_light_model(const class model& model);

    btDiscreteDynamicsWorld* get_dynamics_world();

private:
    std::unique_ptr<class engine_pimpl> pimpl_;

protected:
    void set_game_running(bool is_game_running);

    void start_objects();

    void update_objects();

    void render_objects();

    void render_objects_gui();

    std::unique_ptr<input_manager> input_manager_ =
        std::make_unique<input_manager>();

    std::string game_title_;

    std::vector<std::unique_ptr<game_object>> objects_;

protected:

private:
    bool game_running_ = false;

    float time_       = 0.f;
    float delta_time_ = 0.f;

    movable_object camera_position_;
    movable_object light_position_;

    std::unique_ptr<class input_component> input_component_;

    std::unique_ptr<class video_component> video_component_;

    std::unique_ptr<class gui_component> gui_component_;

    // TODO move physics to a separate component
private:
    void init_physics();

    void update_physics();

    void render_lights();
};

std::unique_ptr<engine> make_engine();

} // namespace pt