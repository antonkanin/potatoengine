#pragma once

#include <engine.hpp>
#include <game_object.hpp>
#include <imgui.h>
#include <key_code.hpp>
#include <movable_object.hpp>

class camera_gui_controller : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override { get_engine().get_camera().set_position(get_position()); }

    void update() override {}

    void on_gui() override
    {
        ImGui::SetNextWindowPos(ImVec2(800, 0), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(200, 150), ImGuiCond_Appearing);

        if (!ImGui::Begin("Camera", nullptr, 0 /*ImGuiWindowFlags_NoTitleBar*/))
        {
            ImGui::End();
            return;
        }

        // camera position

        auto pos = get_engine().get_camera().get_position();

        ImGui::SliderFloat("x", &pos.x, -10.0f, 10.0f, "%.4f", 2.0f);
        ImGui::SliderFloat("y", &pos.y, -10.0f, 10.0f, "%.4f", 2.0f);
        ImGui::SliderFloat("z", &pos.z, -10.0f, 10.0f, "%.4f", 2.0f);

        set_position(pos);
        get_engine().get_camera().set_position(pos);

        // camera direction (Yaw)

        ImGui::Text("Yaw:");
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::PushButtonRepeat(true);
        if (ImGui::ArrowButton("##left", ImGuiDir_Left))
        {
            get_engine().get_camera().add_yaw(-.1f);
        }
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        if (ImGui::ArrowButton("##right", ImGuiDir_Right))
        {
            get_engine().get_camera().add_yaw(.1f);
        }

        // camera direction (Pitch)
        ImGui::Text("Pitch:");
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::PushButtonRepeat(true);
        if (ImGui::ArrowButton("##up", ImGuiDir_Up))
        {
            get_engine().get_camera().add_pitch(-.1f);
        }
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        if (ImGui::ArrowButton("##down", ImGuiDir_Down))
        {
            get_engine().get_camera().add_pitch(.1f);
        }

        ImGui::End();
    }
};