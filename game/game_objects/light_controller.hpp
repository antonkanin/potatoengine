#pragma once

#include <engine.hpp>
#include <game_object.hpp>

class light_controller final : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override
    {
        get_engine().set_light_model("res/cube/cube.obj");

        // sync game object and light positions
        get_engine().get_light().set_position(get_position());
    }

    void update() override {}

    void on_gui() override
    {
        ImGui::SetNextWindowPos(ImVec2(400, 0), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Appearing);

        if (!ImGui::Begin("Light", nullptr, 0 /*ImGuiWindowFlags_NoTitleBar*/))
        {
            ImGui::End();
            return;
        }

        auto pos = get_engine().get_light().get_position();

        ImGui::SliderFloat("x", &pos.x, -10.0f, 10.0f, "%.4f", 2.0f);
        ImGui::SliderFloat("y", &pos.y, -10.0f, 10.0f, "%.4f", 2.0f);
        ImGui::SliderFloat("z", &pos.z, -10.0f, 10.0f, "%.4f", 2.0f);

        get_engine().get_light().set_position(pos);

        set_position(pos);

        ImGui::End();
    }
};
