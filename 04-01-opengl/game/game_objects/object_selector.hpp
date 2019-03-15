#include <engine.hpp>
#include <game_object.hpp>
#include <input_manager.hpp>
#include <iostream>
#include <movable_object.hpp>

#include <SDL2/SDL_mouse.h> // TODO hide this in the engine
#include <glm/gtc/matrix_transform.hpp>
#include <ptm/glm_to_ptm.hpp>
#include <ptm/vec4.hpp>

class object_selector final : public pt::game_object
{
public:
    void update() override
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::mouse_left))
        {
            auto [from, to] = get_world_ray();

            auto dir = to - from;

            dir = glm::normalize(dir);

            bt_pos = { from.x, from.y, from.z };
            bt_dir = { dir.x, dir.y, dir.z };

            btCollisionWorld::ClosestRayResultCallback rayCallBack(
                bt_pos, bt_dir * 100);

            get_engine().get_dynamics_world()->rayTest(bt_pos, bt_dir * 100,
                                                       rayCallBack);

            pt::log_line("Click!");

            if (rayCallBack.hasHit())
            {
                pt::log_line("Hit!");
            }

            is_draw_line = true;
        }

        if (is_draw_line)
        {
            get_engine().draw_line(btvec2ptm(bt_pos),
                                   btvec2ptm(bt_pos + bt_dir * 20));
        }
    }

    glm::mat4x4 get_ndc2world_matrix()
    {
        auto camera = get_engine().get_camera();

        auto view_matrix = ptm::look_at(
            camera.get_position(), camera.get_direction(), camera.get_up());

        auto tranform_matrix = ptm::get_projection_matrix() * view_matrix;

        return glm::inverse(tranform_matrix);
    }

    std::tuple<glm::vec4, glm::vec4> get_world_ray()
    {
        // get NDC from and to
        auto mouse_ndc = get_mouse_normalized();

        auto from_ndc = glm::vec4{ mouse_ndc.x, mouse_ndc.y, -1.f, 1.f };
        auto to_ndc   = glm::vec4{ mouse_ndc.x, mouse_ndc.y, 0.f, 1.f };

        auto ndc2world_matrix = get_ndc2world_matrix();

        auto from_world = ndc2world_matrix * from_ndc;
        from_world /= from_world.w;

        auto to_world = ndc2world_matrix * to_ndc;
        to_world /= to_world.w;

        return { from_world, to_world };
    }

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

    ptm::vec2 get_mouse_normalized()
    {
        auto window_size = get_engine().get_window_size();

        int x, y;
        SDL_GetMouseState(&x, &y);

        auto mouse_pos =
            normalize_screen_coords(x, y, window_size.x, window_size.y);

        std::cout << mouse_pos << std::endl;

        return { mouse_pos.x, mouse_pos.y };
    }

    ptm::vec3 btvec2ptm(const btVector3& source)
    {
        return { source.x(), source.y(), source.z() };
    }

private:
    btVector3 bt_pos{ 0.f, 0.f, 0.f };
    btVector3 bt_dir{ 0.f, 0.f, 0.f };

    bool is_draw_line = false;
};
