#include <engine.hpp>
#include <game_object.hpp>
#include <input_manager.hpp>
#include <iostream>
#include <movable_object.hpp>

#include "space_ship.hpp"
#include <SDL2/SDL_mouse.h> // TODO hide this in the engine
#include <glm/gtc/matrix_transform.hpp>
#include <ptm/glm_to_ptm.hpp>
#include <ptm/vec4.hpp>

class object_selector final : public pt::game_object
{
public:
    using pt::game_object::game_object;

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

            if (rayCallBack.hasHit())
            {
                auto body = (btRigidBody*)btRigidBody::upcast(
                    rayCallBack.m_collisionObject);

                if (body != nullptr)
                {
                    auto game_obj = get_engine().find_game_object(body);
                    if (game_obj != nullptr)
                    {
                        selected_object_ = dynamic_cast<space_ship*>(game_obj);
                        if (selected_object_ != nullptr)
                        {
                            pt::log_line("Found " + game_obj->get_name());
                        }
                    }
                }
            }
        }
    }

    glm::mat4x4 get_ndc2world_matrix()
    {
        auto camera = get_engine().get_camera();

        auto view_matrix = ptm::look_at(
            camera.get_position(), camera.get_direction(), camera.get_up());

        auto transform_matrix = ptm::get_projection_matrix() * view_matrix;

        return glm::inverse(transform_matrix);
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

        return { mouse_pos.x, mouse_pos.y };
    }

    void on_gui() override
    {
        if (selected_object_ == nullptr)
        {
            return;
        }

        ImGui::SetNextWindowPos(ImVec2(140, 0), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(260, 150), ImGuiCond_Appearing);

        if (!ImGui::Begin("Object properties", nullptr,
                          0 /*ImGuiWindowFlags_NoTitleBar*/))
        {
            ImGui::End();
            return;
        }

        auto pos   = selected_object_->get_position();
        auto scale = selected_object_->get_scale();

        ImGui::LabelText("Name", selected_object_->get_name().c_str());
        ImGui::SliderFloat("x", &pos.x, -10.0f, 10.0f, "%.4f", 2.0f);
        ImGui::SliderFloat("y", &pos.y, -10.0f, 10.0f, "%.4f", 2.0f);
        ImGui::SliderFloat("z", &pos.z, -10.0f, 10.0f, "%.4f", 2.0f);

        ImGui::SliderFloat("scale x", &scale.x, -10.0f, 10.0f, "%.4f", 1.0f);
        ImGui::SliderFloat("scale y", &scale.y, -10.0f, 10.0f, "%.4f", 1.0f);
        ImGui::SliderFloat("scale z", &scale.z, -10.0f, 10.0f, "%.4f", 1.0f);

        ImGui::Checkbox("Auto-rotate", &selected_object_->is_auto_rotate_);

        selected_object_->set_position(pos);
        selected_object_->set_scale(scale);

        ImGui::End();
    }

private:
    btVector3 bt_pos{ 0.f, 0.f, 0.f };
    btVector3 bt_dir{ 0.f, 0.f, 0.f };

    space_ship* selected_object_ = nullptr;
};
