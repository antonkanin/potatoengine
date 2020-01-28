#pragma once

#include "component.hpp"
#include <memory>

namespace pt
{

class game_object;

class cubemesh final : public component
{
public:
    explicit cubemesh(class game_object* game_object);

private:
    std::unique_ptr<class model> model_;

    game_object* game_object_;
};

} // namespace pt
