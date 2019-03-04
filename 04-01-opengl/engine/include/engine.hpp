#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "../src/renderer/triangle.hpp" // TODO need to replace 'triangle' with an
// abstraction instead of including a private header

#include "camera.hpp"
#include "input_manager.hpp"
#include "key_code.hpp"
#include "transformation.hpp"
#include "game_object.hpp"

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

    input_manager& get_input_manager();

    void set_title(const std::string& title);

    /** time from the start of the game */
    float time() const;

    /** duration of the previous frame */
    float delta_time() const;

    camera& get_camera() { return camera_; }

protected:
    // virtual void load_models() = 0;

    virtual void poll_events() = 0;

    virtual void post_render_objects() = 0;

    virtual float get_ticks() = 0;

    void set_game_running(bool is_game_running);

    void start_objects();

    void update_objects();

    void render_objects();

    virtual void render_object(const model&          model,
                               const transformation& transformation) = 0;

    std::unique_ptr<input_manager> input_manager_ =
        std::make_unique<input_manager>();

    std::string game_title_;

    std::vector<std::unique_ptr<game_object>> objects_;

private:
    bool game_running_ = false;

    float time_       = 0.f;
    float delta_time_ = 0.f;

    camera camera_;
};

std::unique_ptr<engine> make_engine();

} // namespace pt