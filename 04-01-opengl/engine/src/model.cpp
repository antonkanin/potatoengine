#include "model.hpp"

#include "model_utils.hpp"

namespace pt
{

model::model(const std::string& path)
{
    // path_ = path;
    load_model(*this, path);
}

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