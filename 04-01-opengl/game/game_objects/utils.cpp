#include "utils.hpp"

#include <SDL2/SDL_mouse.h>
#include <game_object.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <log_utils.hpp>
#include <movable_object.hpp>
#include <ptm/glm_to_ptm.hpp>
#include <ptm/math.hpp>

ptm::vec2 normalize_screen_coords(int x, int y, int width, int height)
{
    auto x_f      = static_cast<float>(x);
    auto y_f      = static_cast<float>(y);
    auto width_f  = static_cast<float>(width);
    auto height_f = static_cast<float>(height);

    auto result_x = 2.f * (x_f - (width_f / 2.f)) / width_f;
    auto result_y = 2.f * (y_f - (height_f / 2.f)) / height_f;

    return { result_x, -result_y };
}

ptm::vec2 get_mouse_normalized(pt::engine& engine)
{
    auto window_size = engine.get_window_size();

    int x, y;
    SDL_GetMouseState(&x, &y);

    auto mouse_pos =
        normalize_screen_coords(x, y, window_size.x, window_size.y);

    return { mouse_pos.x, mouse_pos.y };
}

glm::mat4x4 get_ndc2world_matrix(pt::engine& engine)
{
    auto camera = engine.get_camera();

    auto view_matrix = ptm::look_at(camera.get_position(),
                                    camera.get_direction(), camera.get_up());

    auto transform_matrix = ptm::get_projection_matrix() * view_matrix;

    return glm::inverse(transform_matrix);
}

std::tuple<glm::vec4, glm::vec4> get_mouse_ndc(pt::engine& engine)
{
    // get NDC from and to
    const auto mouse_ndc = get_mouse_normalized(engine);

    const auto from_ndc = glm::vec4{ mouse_ndc.x, mouse_ndc.y, -1.f, 1.f };
    const auto to_ndc   = glm::vec4{ mouse_ndc.x, mouse_ndc.y, 0.f, 1.f };

    return { from_ndc, to_ndc };
}

std::tuple<glm::vec4, glm::vec4> get_world_ray(pt::engine& engine,
                                               glm::vec4   from_ndc,
                                               glm::vec4   to_ndc)
{
    auto ndc2world_matrix = get_ndc2world_matrix(engine);

    auto from_world = ndc2world_matrix * from_ndc;
    from_world /= from_world.w;

    auto to_world = ndc2world_matrix * to_ndc;
    to_world /= to_world.w;

    return { from_world, to_world };
}

pt::game_object* find_collision(pt::engine& engine, const glm::vec4& from_ndc,
                                const glm::vec4& to_ndc)
{
    pt::log_line("key down");

    auto [from, to] = get_world_ray(engine, from_ndc, to_ndc);

    auto dir = to - from;

    dir = glm::normalize(dir);

    btVector3 bt_pos = { from.x, from.y, from.z };
    btVector3 bt_dir = { dir.x, dir.y, dir.z };

    btCollisionWorld::ClosestRayResultCallback rayCallBack(bt_pos,
                                                           bt_dir * 100);

    engine.get_dynamics_world()->rayTest(bt_pos, bt_dir * 100, rayCallBack);

    if (rayCallBack.hasHit())
    {
        auto body =
            (btRigidBody*)btRigidBody::upcast(rayCallBack.m_collisionObject);

        if (body != nullptr)
        {
            auto found_object = engine.find_game_object(body);

            if (found_object != nullptr)
            {
                return found_object;
            }
        }
    }

    return nullptr;
}
