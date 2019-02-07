#pragma once

#include <memory>

namespace pt
{
class engine
{
public:
    void run();

protected:
    virtual bool init() = 0;

    virtual bool poll_events(Event& ev) = 0;

    virtual void process_input(const Event& ev) = 0;
};

std::unique_ptr<engine> make_engine();

} // namespace pt