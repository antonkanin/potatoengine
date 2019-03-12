#pragma once

#include <memory>

namespace pt
{

class input_component_pimpl;

class input_component
{
public:
    explicit input_component();

    bool init();

    void poll_events(class input_manager& input_manager);

private:
    //std::unique_ptr<input_component_pimpl> pimpl_;
    input_component_pimpl* pimpl_;
};

} // namespace pt
