#include "model.hpp"
#include <cstdlib>

namespace pt
{

model::model(const model& source)
{
    this->vertices =
        static_cast<vertex*>(malloc(source.vert_count * sizeof(vertex)));
    std::memcpy(this->vertices, source.vertices, source.vert_count);
    this->vert_count = source.vert_count;

    this->indices = static_cast<unsigned short*>(
        malloc(source.vert_count * sizeof(vertex)));
    std::memcpy(this->indices, source.indices, source.ind_count);
    this->ind_count = source.ind_count;
}

model& model::operator=(const model& source)
{
    this->vertices =
        static_cast<vertex*>(malloc(source.vert_count * sizeof(vertex)));
    std::memcpy(this->vertices, source.vertices,
                source.vert_count * sizeof(vertex));
    this->vert_count = source.vert_count;

    this->indices = static_cast<unsigned short*>(
        malloc(source.vert_count * sizeof(unsigned short)));
    std::memcpy(this->indices, source.indices,
                source.ind_count * sizeof(unsigned short));
    this->ind_count = source.ind_count;

    return *this;
}

} // namespace pt