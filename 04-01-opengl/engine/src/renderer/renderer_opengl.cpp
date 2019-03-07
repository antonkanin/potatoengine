#include "renderer_opengl.hpp"
#include "opengl_utils.hpp"
#include "program.hpp"
#include "ptm/math.hpp"
#include "ptm/matrix.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_sdl.h"

#include <iostream>

namespace pt
{

const glm::mat4x4 perspective_matrix_ =
    glm::perspective<float>(glm::pi<float>() / 2, 4.f / 3, 0.1f, 100.0f);

// const glm::mat4x4 perspective_matrix_ = glm::mat4x4();

std::ostream& operator<<(std::ostream& out, const glm::vec4& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
    return out;
}

glm::vec3 glm_vec(const vec3 vector)
{
    return { vector.x, vector.y, vector.z };
}

glm::mat4x4 glm_mat(const ptm::matrix4x4& mat)
{
    glm::mat4x4 result;

    result[0].x = mat.row1.x;
    result[1].x = mat.row1.y;
    result[2].x = mat.row1.z;
    result[3].x = mat.row1.w;

    result[0].y = mat.row2.x;
    result[1].y = mat.row2.y;
    result[2].y = mat.row2.z;
    result[3].y = mat.row2.w;

    result[0].z = mat.row3.x;
    result[1].z = mat.row3.y;
    result[2].z = mat.row3.z;
    result[3].z = mat.row3.w;

    result[0].w = mat.row4.x;
    result[1].w = mat.row4.y;
    result[2].w = mat.row4.z;
    result[3].w = mat.row4.w;

    return result;
}

glm::mat4x4 look_at(const vec3& position, const vec3& direction, const vec3& up)
{
    return glm::lookAt(glm_vec(position), glm_vec(position + direction),
                       glm_vec(up));
}

glm::mat4 renderer_opengl::get_transform_matrix(
    const transformation& transformation, const movable_object& camera) const
{
    ///////////////////////////////////////////////////////////////////////////
    // make scale matrix

    glm::mat4x4 scale_m =
        glm::scale(glm::mat4x4(), glm_vec(transformation.scale));

    ///////////////////////////////////////////////////////////////////////////
    // make rotation matrix

    ptm::matrix4x4 rotation_m = ptm::matrix4x4(ptm::rotation(
        transformation.rotation_angle, transformation.rotation_vector));

    glm::mat4 rotate_m = glm_mat(rotation_m);

    ///////////////////////////////////////////////////////////////////////////
    // make translation matrix

    ptm::matrix4x4 translation_m = ptm::translation(transformation.position);

    glm::mat4 translate_m = glm_mat(translation_m);

    ///////////////////////////////////////////////////////////////////////////

    glm::mat4 view_m = get_view_matrix(camera);

    ///////////////////////////////////////////////////////////////////////////
    // make full transformation matrix

    glm::mat4 full_transfom_m =
        perspective_matrix_ * view_m * translate_m * rotate_m * scale_m;

    return full_transfom_m;
}

glm::mat4 renderer_opengl::get_view_matrix(const movable_object& camera) const
{
    glm::mat4 view_m =
        look_at(camera.get_position(), camera.get_direction(), camera.get_up());
    return view_m;
}

void renderer_opengl::render_model(const model&          model,
                                   const transformation& transformation,
                                   const movable_object& camera,
                                   const ptm::vec3&      light_position)
{

    generic_program_->use();

    auto full_transform_m = get_transform_matrix(transformation, camera);

    generic_program_->set_matrix4("u_transform_matrix",
                                  glm::value_ptr(full_transform_m));

    generic_program_->set_vec3("u_light_pos", light_position);

    generic_program_->validate();

    model.draw(*(generic_program_.get()));
}

void renderer_opengl::render_light(const model&          model,
                                   const vec3&           light_position,
                                   const movable_object& camera)
{
    ptm::matrix4x4 translation_m = ptm::translation(light_position);

    glm::mat4 translate_m = glm_mat(translation_m);

    glm::mat4 view_m = get_view_matrix(camera);

    glm::mat4 full_transform_m = perspective_matrix_ * view_m * translate_m;

    light_program_->use();

    light_program_->set_matrix4("u_transform_matrix",
                                glm::value_ptr(full_transform_m));
    light_program_->validate();

    model.draw(*(light_program_.get()));
}

bool renderer_opengl::initialize(SDL_Window* window)
{
    using namespace std;

    renderer::initialize(window);

    initialize_gl_functions();

    set_opengl_version();

    if (!create_opengl_context())
    {
        return false;
    }

    print_opengl_version();

    generic_program_ = make_unique<program>("shaders/generic_shader.vert",
                                            "shaders/generic_shader.frag");
    light_program_   = make_unique<program>("shaders/light_shader.vert",
                                          "shaders/light_shader.frag");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    check_gl_errors();

    init_imgui(window_);

    return true;
}

void renderer_opengl::swap_buffers()
{
    SDL_GL_SwapWindow(window_);

    glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
    check_gl_errors();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    check_gl_errors();
}

bool renderer_opengl::create_opengl_context()
{
    gl_context_ = SDL_GL_CreateContext(window_);

    if (gl_context_ == nullptr)
    {
        std::cout << "error: count not create OpenGL context: "
                  << SDL_GetError() << '\n';
        return false;
    }

    SDL_assert(gl_context_ != nullptr);

    return true;
}

void renderer_opengl::enable_vsync(bool state)
{
    SDL_GL_SetSwapInterval(state ? 1 : 0);
}

void renderer_opengl::render_gui_frame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void renderer_opengl::init_imgui(SDL_Window* window)
{
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
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context_);
    ImGui_ImplOpenGL3_Init(nullptr);
}

void renderer_opengl::prepare_gui_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window_);
    ImGui::NewFrame();
}

void renderer_opengl::enable_wireframe(bool state)
{
    if (state)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

} // namespace pt
