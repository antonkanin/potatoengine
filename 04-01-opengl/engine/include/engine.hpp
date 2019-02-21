#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "../src/renderer/triangle.hpp" // TODO need to replace 'triangle' with an
// abstraction instead of including a private header

#include "game_object.hpp"
#include "input_manager.hpp"
#include "key_code.hpp"

namespace pt
{

class engine
{
public:
    virtual ~engine() = default;

    virtual bool init() = 0;

    virtual bool run() = 0;

    void add_object(std::unique_ptr<game_object> object);

    input_manager& get_input_manager();

    void set_title(const std::string& title);

protected:
    void start_objects();

    void update_objects();

    void render_objects();

    virtual void render_object(const vector3d& position) = 0;

    std::unique_ptr<input_manager> input_manager_ =
        std::make_unique<input_manager>();

    std::string game_title_;

private:
    std::vector<std::unique_ptr<game_object>> objects_;
};

std::unique_ptr<engine> make_engine();

} // namespace pt