#include "vertex_buffer.hpp"

namespace pt
{

vertex_buffer::vertex_buffer() = default;

vertex_buffer::~vertex_buffer() = default;

vertex_buffer_opengl::vertex_buffer_opengl(unsigned int VAO)
    : VAO_(VAO)
{
}
}