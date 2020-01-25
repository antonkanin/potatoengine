#pragma once

#include "renderer/program.hpp"
#include <memory>

namespace pt
{

class material
{
    virtual void init() {}

    std::unique_ptr<program> program;

    void activate()
    {

    }
};

class fur_material : public material
{
    void init()
    {
        // generate fur texture
    }
};

}