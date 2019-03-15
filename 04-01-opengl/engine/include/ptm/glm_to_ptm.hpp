#pragma once

#include <ptm/vec3.hpp>

namespace ptm
{

inline glm::vec3 glm_vec(const vec3 vector)
{
    return { vector.x, vector.y, vector.z };
}

inline glm::mat4x4 look_at(const vec3& position, const vec3& direction,
                           const vec3& up)
{
    return glm::lookAt(glm_vec(position), glm_vec(position + direction),
                       glm_vec(up));
}

inline glm::mat4x4 get_projection_matrix()
{
    return glm::perspective<float>(glm::pi<float>() / 2, 4.f / 3, 0.1f, 100.0f);
}

} // namespace ptm
