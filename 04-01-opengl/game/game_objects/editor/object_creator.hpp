#include <file_utils.hpp>
#include <game_object.hpp>
#include <game_objects_list.hpp>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <input_manager.hpp>
#include <log_utils.hpp>

class object_creator final : public pt::game_object
{
private:
    using pt::game_object::game_object;

    void start() override {}

    void update() override
    {
        if (get_engine().get_input_manager().get_key_down(pt::key_code::F12))
        {
            get_engine().cursor_locked(!get_engine().cursor_locked());
        }
    }

    void on_gui() override
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Appearing);

        if (!ImGui::Begin("New object", nullptr,
                          0 /*ImGuiWindowFlags_NoTitleBar*/))
        {
            ImGui::End();
            return;
        }

        show_existing_objects();

        show_object_properties();

        // ImGui::ShowDemoWindow(nullptr);

        ImGui::End();
    }

    void save_scene() { pt::save_scene(get_engine(), "scenes/test.yaml"); }

    void show_existing_objects()
    {
        int new_current_item = current_item_;

        ImGui::ListBox("", &new_current_item,
                       get_engine().objects().get_names(),
                       static_cast<int>(get_engine().objects().size()), 10);

        if (new_current_item != current_item_)
        {
            current_item_   = new_current_item;
            current_object_ = &get_engine().objects()[current_item_];

            object_name_     = current_object_->get_name();
            object_position_ = current_object_->get_position();
            object_scale_    = current_object_->get_scale();
        }
    }

    void show_object_type_combo()
    {
        static int item_current = 0;

        const auto& types = get_engine().object_types();

        ImGui::Combo("combo", &item_current, types.data(),
                     static_cast<int>(types.size()));
    }

    void show_object_properties()
    {
        if (nullptr == current_object_)
        {
            return;
        }

        ImGui::InputText("Name", &object_name_);

        ImGui::Spacing();

        ImGui::Text("Position");
        ImGui::InputFloat("x##pos", &object_position_.x, 0.1f, 1.0f);
        ImGui::InputFloat("y##pos", &object_position_.y, 0.1f, 1.0f);
        ImGui::InputFloat("z##pos", &object_position_.z, 0.1f, 1.0f);

        ImGui::Text("Scale");
        ImGui::InputFloat("x##scale", &object_scale_.x, 0.1f, 1.0f);
        ImGui::InputFloat("y##scale", &object_scale_.y, 0.1f, 1.0f);
        ImGui::InputFloat("z##scale", &object_scale_.z, 0.1f, 1.0f);

        // TODO add option to change object names
        // get_engine().objects().update_name(current_object_, object_name_);
        current_object_->set_position(object_position_);
        current_object_->set_scale(object_scale_);

        ImGui::Spacing();

        if (ImGui::Button("Save Scene"))
        {
            pt::log_line("Scene saved");
            save_scene();
        }
    }

    game_object* current_object_ = nullptr;

    int current_item_ = -1;

    std::string object_name_;
    ptm::vec3   object_position_{ 0.f, 0.f, 0.f };
    ptm::vec3   object_scale_{ 1.f, 1.f, 1.f };
};
