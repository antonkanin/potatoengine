#pragma once

#include <iostream>
#include <memory>
#include <vector>

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

protected:
    void update_objects();

    std::unique_ptr<input_manager> input_manager_ =
        std::make_unique<input_manager>();

private:
    std::vector<std::unique_ptr<game_object>> objects_;
};

std::unique_ptr<engine> make_engine();

} // namespace pt