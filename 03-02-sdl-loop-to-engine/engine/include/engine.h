#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "input_manager.h"
#include "key_code.h"

namespace pt
{

class game_object;

class engine
{
public:
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