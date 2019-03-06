#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "../src/renderer/triangle.hpp" // TODO need to replace 'triangle' with an
// abstraction instead of including a private header

#include "game_object.hpp"
#include "input_manager.hpp"
#include "key_code.hpp"
#include "movable_object.hpp"
#include "transformation.hpp"

namespace pt
{

class model;

class engine
{
public:
    virtual ~engine() = default;

    virtual bool init() = 0;

    bool run();

    void add_object(std::unique_ptr<game_object> object);

    template <typename T>
    engine* add_object()
    {
        add_object(std::make_unique<T>());
        return this;
    }

    template <typename T>
    engine* add_object(const ptm::vec3 position)
    {
        auto obj = std::make_unique<T>();
        obj->set_position(position);
        this->add_object(move(obj));
        return this;
    }

    input_manager& get_input_manager();

    void set_title(const std::string& title);

    /** time from the start of the game */
    float time() const;

    /** duration of the previous frame */
    float delta_time() const;

    movable_object& get_camera() { return camera_; }

    movable_object& get_light() { return light_; }

    virtual void enable_vsync(bool state) = 0;

protected:
    // virtual void load_models() = 0;

    virtual void poll_events() = 0;

    virtual void post_render_objects() = 0;

    virtual float get_ticks() = 0;

    void set_game_running(bool is_game_running);

    void start_objects();

    void update_objects();

    void render_objects();

    void render_objects_gui();

    virtual void render_object(const model&          model,
                               const transformation& transformation,
                               const ptm::vec3&      light_position) = 0;

    virtual void prepare_gui_frame() = 0;

    virtual void render_gui_frame() = 0;

    std::unique_ptr<input_manager> input_manager_ =
        std::make_unique<input_manager>();

    std::string game_title_;

    std::vector<std::unique_ptr<game_object>> objects_;

private:
    bool game_running_ = false;

    float time_       = 0.f;
    float delta_time_ = 0.f;

    movable_object camera_;
    movable_object light_;
};

std::unique_ptr<engine> make_engine();

} // namespace pt