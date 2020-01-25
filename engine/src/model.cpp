#include "model.hpp"
#include "mesh.hpp"

namespace pt
{

void model::add_mesh(mesh_ptr& mesh_value)
{
    meshes_.push_back(std::move(mesh_value));
}

} // namespace pt