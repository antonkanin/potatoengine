#pragma once

#include <vector>

namespace pt
{

class vertex_buffer
{
public:
    virtual ~vertex_buffer() = default;
};

class vertex_buffer_opengl : public vertex_buffer
{
public:
    explicit vertex_buffer_opengl(unsigned int VAO)
        : vertex_buffer()
        , VAO_{ VAO } {};

    unsigned int VAO_ = 0;
};

}