#include "gui_component.hpp"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

namespace pt
{

class gui_component_pimpl
{
public:
    SDL_Window* window_ = nullptr;
};

gui_component::gui_component()
    : pimpl_(std::make_unique<gui_component_pimpl>())
{
}

void gui_component::prepare_gui_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(pimpl_->window_);
    ImGui::NewFrame();
}

void gui_component::init(SDL_Window* window)
{
    pimpl_->window_ = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard
    // Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void gui_component::render_gui_frame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

gui_component::~gui_component() = default;

} // namespace pt