#include "model.hpp"

namespace pt
{

model::model(const model& source)
{
    std::memcpy(this->vertices, source.vertices, source.vert_count);
    this->vert_count = source.vert_count;

    std::memcpy(this->indices, source.indices, source.ind_count);
    this->ind_count = source.ind_count;
}

} // namespace pt