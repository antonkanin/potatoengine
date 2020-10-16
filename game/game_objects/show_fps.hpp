#include <game_object.hpp>
#include <imgui.h>

class show_fps final : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override
    {
        /*get_engine().enable_vsync(false);*/
        // physics_on_ = get_engine().is_physics_enabled();

        physics_on_ = false;
    }

    void update() override
    {
        delta_ += get_engine().delta_time();
        ++frames_count_;

        if (delta_ >= 1.f)
        {
            frames_str_   = std::to_string(frames_count_);
            frames_count_ = 0;
            delta_        = 0;
        }
    }

    void on_gui() override
    {
        bool is_show = false;
        // ImGui::ShowDemoWindow(&is_show);
        ImGui::SetNextWindowPos(ImVec2(300, 0), ImGuiCond_Appearing);
        ImGui::SetNextWindowSize(ImVec2(120, 100), ImGuiCond_Appearing);

        // ImGuiWindowFlags window_flags = 0;
        if (!ImGui::Begin("FPS", &is_show, ImGuiWindowFlags_NoTitleBar))
        {
            ImGui::End();
            return;
        }

        ImGui::Text(frames_str_.c_str());
        ImGui::Checkbox("wireframe", &wireframe_on_);
        ImGui::Checkbox("physics", &physics_on_);

        ImGui::End();

        get_engine().enable_wireframe(wireframe_on_);
        get_engine().enable_physics(physics_on_);
    }

private:
    float        delta_        = 0.f;
    unsigned int frames_count_ = 0;
    std::string  frames_str_   = "";
    bool         wireframe_on_ = false;
    bool         physics_on_   = false;
};
