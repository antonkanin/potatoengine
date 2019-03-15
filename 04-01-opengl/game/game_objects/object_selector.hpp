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
            auto dir = get_engine().get_camera().get_direction();
            auto pos = get_engine().get_camera().get_position();

            auto bt_dir = btVector3{ dir.x, dir.y, dir.z };
            auto bt_pos = btVector3{ pos.x, pos.y, pos.z };

            btCollisionWorld::ClosestRayResultCallback rayCallBack(
                bt_pos, bt_dir * 100);

            get_engine().get_dynamics_world()->rayTest(bt_pos, bt_dir * 100,
                                                       rayCallBack);

            pt::log_line("Click!");

            if (rayCallBack.hasHit())
            {
                pt::log_line("Hit!");
            }
        }

        auto camera = get_engine().get_camera();

        auto view_matrix = ptm::look_at(
            camera.get_position(), camera.get_direction(), camera.get_up());

        auto tranform_matrix   = ptm::get_projection_matrix() * view_matrix;
        auto screen_to_world_m = glm::inverse(tranform_matrix);
    }

    ptm::vec2 normalize_screen_coords(int x, int y, int width, int height)
    {
        auto x_f      = static_cast<float>(x);
        auto y_f      = static_cast<float>(y);
        auto width_f  = static_cast<float>(width);
        auto height_f = static_cast<float>(height);

        auto result_x = x_f - (width_f / 2.f) / width_f;
        auto result_y = y_f - (height_f / 2.f) / height_f;

        return { result_x, result_y };
    }

    ptm::vec4 get_mouse_pos()
    {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        auto Width  = DM.w;
        auto Height = DM.h;

        int x, y;
        SDL_GetMouseState(&x, &y);

        auto mouse_pos = normalize_screen_coords(x, y, Width, Height);

        return { mouse_pos.x, mouse_pos.y, 0.f, 1.0f };
    }

public:
};
