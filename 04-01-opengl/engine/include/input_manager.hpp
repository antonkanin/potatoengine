#pragma once

#include "key_code.hpp"
#include <map>

namespace pt
{

class engine;

class input_manager
{
public:
    input_manager();

    bool get_key_down(const key_code& key_code) const;

    bool get_key_up(const key_code& key_code) const;

    bool& key_code_state(const key_code& code, const key_state& state);

    void reset_states();

    void  set_axis_x(float value){ axis_x_ = value; };
    float get_axis_x() const { return axis_x_; }

    void  set_axis_y(float value){ axis_y_ = value; };
    float get_axis_y() const { return axis_y_; }

private:
    std::map<key_code, std::map<key_state, bool>> keys_;

    float axis_x_ = 0.f;
    float axis_y_ = 0.f;
};

} // namespace pt