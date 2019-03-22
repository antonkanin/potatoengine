#include <file_utils.hpp>
#include <game_object.hpp>
#include <game_objects_list.hpp>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <log_utils.hpp>

class object_creator final : public pt::game_object
{
private:
    using pt::game_object::game_object;

    void start() override {}

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

        show_existing_objects();

        show_object_properties();

        ImGui::ShowDemoWindow(nullptr);

        ImGui::End();
    }

    void save_scene() { pt::save_scene(get_engine(), "scenes/test.yaml"); }

    void show_existing_objects()
    {
        static int current_item = 1;

        ImGui::ListBox("listbox\n(single select)", &current_item,
                       get_engine().objects().get_names(),
                       static_cast<int>(get_engine().objects().size()), 4);
    }

    void show_object_properties()
    {
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
            obj->set_position({ x, y, z })->add_body(false);
        }

        ImGui::Spacing();
        if (ImGui::Button("Save Scene"))
        {
            pt::log_line("Scene saved");
            save_scene();
        }
    }

    std::string object_name;
    float       x = 0.f;
    float       y = 0.f;
    float       z = 0.f;
};
