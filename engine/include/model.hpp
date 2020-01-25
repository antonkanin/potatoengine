#pragma once

#include <memory>
#include <vector>

namespace pt
{

using mesh_ptr = std::unique_ptr<class mesh>;

class model
{
public:
    void add_mesh(mesh_ptr&);

    std::vector<mesh_ptr>&       get_meshes() { return meshes_; }
    const std::vector<mesh_ptr>& get_meshes() const { return meshes_; }

private:
    std::vector<mesh_ptr> meshes_;
};

} // namespace pt