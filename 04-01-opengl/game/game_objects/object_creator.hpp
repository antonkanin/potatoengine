#include <game_object.hpp>
#include <log_utils.hpp>
#include <imgui_stdlib.h>
#include <imgui.h>
#include <file_utils.hpp>


class object_creator final : public pt::game_object
{
private:
    using pt::game_object::game_object;

    void on_gui() override
    {
        ImGui::SetNextWindowPos(ImVec2(140, 0), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Appearing);

        if (!ImGui::Begin("New object", nullptr,
                          0 /*ImGuiWindowFlags_NoTitleBar*/))
        {
            ImGui::End();
            return;
        }

        ///////////////////////////////////////////////////////////////////////
        // combo box

        static int item_current = 0;

        const auto& types = get_engine().object_types();

        ImGui::Combo("combo", &item_current, types.data(),
                     static_cast<int>(types.size()));

        auto class_name = types[item_current];

        ///////////////////////////////////////////////////////////////////////
        // edit box

        ImGui::InputText("Name", &object_name);
        ImGui::InputFloat("x", &x);
        ImGui::InputFloat("y", &y);
        ImGui::InputFloat("z", &z);

        ///////////////////////////////////////////////////////////////////////
        // button

        if (ImGui::Button("Button"))
        {
            auto obj = get_engine().make_object(class_name, object_name);
            obj->set_position({x, y, z})->add_body(false);
        }

        ImGui::Spacing();
        if (ImGui::Button("Save Scene"))
        {
            pt::log_line("Scene saved");
            save_scene();
        }

        //ImGui::ShowDemoWindow(nullptr);

        ImGui::End();
    }

    void save_scene()
    {
        pt::save_scene(get_engine(), "scenes/test.yaml");
    }

    std::string object_name;
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
};
