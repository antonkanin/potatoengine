#include <engine.hpp>
#include <game_object.hpp>
#include <input_manager.hpp>
#include <iostream>
#include <movable_object.hpp>

#include "../space_ship.hpp"

#include <SDL2/SDL_mouse.h> // TODO hide this in the engine
#include <glm/gtc/matrix_transform.hpp>
#include <ptm/glm_to_ptm.hpp>
#include <ptm/math.hpp>
#include <ptm/vec4.hpp>

#include "../game/enemy.hpp"
#include "../utils.hpp"

class object_selector final : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void update() override
    {
        handle_mouse_input();

        draw_debug_line();
    }

    void draw_debug_line()
    {
        get_engine().draw_line(line_from_, line_to_, { 1.0f, 0.0f, 0.0f });

        // pt::log_line() << line_from_ << line_to_ << std::endl;
    }

    void handle_mouse_input()
    {
        if (get_engine().get_input_manager().get_key_down(
                pt::key_code::mouse_left))
        {
            const auto [mouse_from, mouse_to] = get_mouse_ndc();

            auto [mouse_world_from, mouse_world_to] =
                get_world_ray(get_engine(), mouse_from, mouse_to);

            line_from_ = { mouse_world_from.x, mouse_world_from.y,
                           mouse_world_from.z };

            line_to_ = { mouse_world_to.x, mouse_world_to.y, mouse_world_to.z };
            line_to_ = line_from_ + 10 * ptm::normalize(line_to_ - line_from_);

            auto found_obj =
                find_collision(get_engine(), mouse_world_from, mouse_world_to);

            if (found_obj != nullptr)
            {
                selected_object_ = found_obj;
            }
        }
    }

    std::tuple<glm::vec4, glm::vec4> get_mouse_ndc()
    {
        // get NDC from and to
        const auto mouse_ndc = get_mouse_normalized();

        const auto from_ndc = glm::vec4{ mouse_ndc.x, mouse_ndc.y, -1.f, 1.f };
        const auto to_ndc   = glm::vec4{ mouse_ndc.x, mouse_ndc.y, 1.f, 1.f };

        return { from_ndc, to_ndc };
    }

    static ptm::vec2 normalize_screen_coords(int x, int y, int width,
                                             int height)
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

        ImGui::Text("Position");
        ImGui::InputFloat("x##pos", &pos.x, 0.1f, 1.0f);
        ImGui::InputFloat("y##pos", &pos.y, 0.1f, 1.0f);
        ImGui::InputFloat("z##pos", &pos.z, 0.1f, 1.0f);

        ImGui::Text("Scale");
        ImGui::InputFloat("x##scale", &scale.x, 0.1f, 1.0f);
        ImGui::InputFloat("y##scale", &scale.y, 0.1f, 1.0f);
        ImGui::InputFloat("z##scale", &scale.z, 0.1f, 1.0f);

        //        ImGui::SliderFloat("x", &pos.x, -10.0f, 10.0f, "%.4f", 2.0f);
        //        ImGui::SliderFloat("y", &pos.y, -10.0f, 10.0f, "%.4f", 2.0f);
        //        ImGui::SliderFloat("z", &pos.z, -10.0f, 10.0f, "%.4f", 2.0f);
        //
        //        ImGui::SliderFloat("scale x", &scale.x, -10.0f, 10.0f,
        //        "%.4f", 1.0f); ImGui::SliderFloat("scale y", &scale.y,
        //        -10.0f, 10.0f, "%.4f", 1.0f); ImGui::SliderFloat("scale z",
        //        &scale.z, -10.0f, 10.0f, "%.4f", 1.0f);

        // ImGui::Checkbox("Auto-rotate", &selected_object_->is_auto_rotate_);

        selected_object_->set_position(pos);
        selected_object_->set_scale(scale);

        ImGui::End();
    }

private:
    //    btVector3 bt_pos{ 0.f, 0.f, 0.f };
    //    btVector3 bt_dir{ 0.f, 0.f, 0.f };

    ptm::vec3 line_from_;
    ptm::vec3 line_to_;

    game_object* selected_object_ = nullptr;
};
