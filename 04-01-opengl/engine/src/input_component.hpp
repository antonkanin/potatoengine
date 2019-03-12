#pragma once

#include <memory>

namespace pt
{

class input_component
{
public:
    explicit input_component();

    ~input_component();

    bool init();

    void poll_events(class input_manager& input_manager);

private:
    std::unique_ptr<class input_component_pimpl> pimpl_;
};

} // namespace pt
