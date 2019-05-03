#pragma once

#include <vector>

#include "opengl_utils.hpp"
#include "vertex.hpp"

namespace pt
{

class vertex_buffer
{
public:
    vertex_buffer();

    virtual ~vertex_buffer();
};

class vertex_buffer_opengl : public vertex_buffer
{
public:
    explicit vertex_buffer_opengl(unsigned int VAO);

private:
    unsigned int VAO_ = 0;
};

}