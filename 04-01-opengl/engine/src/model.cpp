#include "model.hpp"
#include "model_utils.hpp"
#include "mesh.hpp"

namespace pt
{

void model::draw(program& program) const
{
    for (auto& mesh : meshes_)
    {
        mesh->draw(program);
    }
}

void model::add_mesh(std::unique_ptr<mesh>& mesh_value)
{
    meshes_.push_back(std::move(mesh_value));
}
model::model() {}

model::~model() {}

} // namespace pt