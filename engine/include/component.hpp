#pragma once

#include <memory>

namespace pt
{

class component
{
public:
    ~component() = default;

    virtual void start() {}
    virtual void update() {}
};

using component_ptr = std::unique_ptr<component>;

} // namespace pt
