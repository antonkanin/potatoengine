#include "model.hpp"

#include "model_utils.hpp"

namespace pt
{

void model::draw(program& program) const
{
    for (auto& mesh : meshes_)
    {
        mesh.draw(program);
    }
}

void model::add_mesh(const mesh& mesh)
{
    meshes_.push_back(mesh);
}

} // namespace pt