#include "video_component.hpp"

#include "mesh.hpp"
#include "model.hpp"
#include "movable_object.hpp"
#include "ptm/math.hpp"
#include "renderer/opengl_utils.hpp"
#include "renderer/program.hpp"
#include "transformation.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "imgui/imgui_impl_sdl.h"

#include <log_utils.hpp>
#include <ptm/glm_to_ptm.hpp>
#include "model_utils.hpp"

namespace pt
{

class video_component_pimpl
{
public:
    void init()
    {
        generic_program_ = std::make_unique<program>(
            "shaders/generic_shader.vert", "shaders/generic_shader.frag");

        light_program_ = std::make_unique<program>("shaders/light_shader.vert",
                                                   "shaders/light_shader.frag");
    }

    std::unique_ptr<program> generic_program_;

    std::unique_ptr<program> light_program_;

    SDL_GLContext gl_context_ = nullptr;

    SDL_Window* window_ = nullptr;
};

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

glm::mat4 get_view_matrix(const movable_object& camera)
{
    glm::mat4 view_m =
        look_at(camera.get_position(), camera.get_direction(), camera.get_up());
    return view_m;
}

glm::mat4 get_model_view_matrix(const transformation& transformation,
                                const movable_object& camera)
{
    ///////////////////////////////////////////////////////////////////////////
    // make scale matrix

    glm::mat4 identity =
        glm::mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4x4 scale_m = glm::scale(identity, glm_vec(transformation.scale));

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

    return view_m * translate_m * rotate_m * scale_m;
}

// TODO use exceptions here instead of returning nullptr
SDL_GLContext create_opengl_context(SDL_Window* window)
{
    auto gl_context = SDL_GL_CreateContext(window);

    if (gl_context == nullptr)
    {
        std::cout << "error: count not create OpenGL context: "
                  << SDL_GetError() << '\n';
        return nullptr;
    }

    SDL_assert(gl_context != nullptr);

    return gl_context;
}

video_component::video_component()
    : impl(std::make_unique<video_component_pimpl>())
{
}

void video_component::render_object(const struct model&          model,
                                    const struct transformation& transformation,
                                    const struct movable_object& camera,
                                    const ptm::vec3& light_position, float time)
{
    impl->generic_program_->use();

    auto model_view_matrix_m = get_model_view_matrix(transformation, camera);

    impl->generic_program_->set_matrix4("u_model_view_matrix",
                                        glm::value_ptr(model_view_matrix_m));

    impl->generic_program_->set_matrix4(
        "u_projection_matrix", glm::value_ptr(get_projection_matrix()));

    auto light_pos = get_view_matrix(camera) *
                     glm::vec4(glm_vec(camera.get_position()), 1.0f);

    impl->generic_program_->set_vec3("u_light_pos",
                                     { light_pos.x, light_pos.y, light_pos.z });

    auto light_direction = get_view_matrix(camera) *
                           glm::vec4(glm_vec(camera.get_direction()), 0.0f);

    impl->generic_program_->set_vec3(
        "u_light_direction",
        { light_direction.x, light_direction.y, light_direction.z });

    impl->generic_program_->set_1f("u_light_angle", M_PI / 10);

    // calculating gravity + light wind wind
    float dx = 0.005f * std::sin(time * 2);

    impl->generic_program_->set_vec3("u_gravity", { dx, -0.01f, 0.0f });

    auto alpha_texture_location_id =
        glGetUniformLocation(impl->generic_program_->id(), "alpha_texture");
    check_gl_errors();

    if (-1 == alpha_texture_location_id)
    {
        throw std::runtime_error(
            "Error: uniform variable alpha_texture not found");
    }

    impl->generic_program_->set_1i("alpha_texture", 0);

    glActiveTexture_(GL_TEXTURE0);
    check_gl_errors();

    glBindTexture(GL_TEXTURE_2D, textureID);
    check_gl_errors();

    impl->generic_program_->validate();

    draw_model(model, *impl->generic_program_);
    //model.draw();
}

bool video_component::init(const std::string& title)
{
    const int init_result = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (init_result != 0)
    {
        SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
        return false;
    }

    const unsigned int WINDOW_WIDTH  = 1024;
    const unsigned int WINDOW_HEIGHT = 768;

    // TODO fix the warning "Warning:(47, 43) Clang-Tidy: Use of a signed
    // integer operand with a binary bitwise operator"
    //    impl->window_ = SDL_CreateWindow(
    //        title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    //        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL |
    //        SDL_WINDOW_RESIZABLE);

    impl->window_ =
        SDL_CreateWindow(title.c_str(), 200, 200, WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (impl->window_ == nullptr)
    {
        SDL_Log("Error: failed to SDL window %s", SDL_GetError());
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return false;
    }

    set_opengl_version();

    impl->gl_context_ = create_opengl_context(impl->window_);

    initialize_gl_functions();

    print_opengl_version();

    glEnable(GL_DEPTH_TEST);
    check_gl_errors();

    impl->init();

    generate_alpha();
    init_alpha_texture();

    return true;
}

void video_component::swap_buffers()
{

    SDL_GL_SwapWindow(impl->window_);

    glClearColor(0.3f, 0.3f, 1.0f, 0.0f); // blue background
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    check_gl_errors();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    check_gl_errors();
}

void video_component::enable_vsync(bool state)
{
    SDL_GL_SetSwapInterval(state ? 1 : 0);
}

float video_component::get_ticks()
{
    return SDL_GetTicks();
}

class SDL_Window* video_component::get_window()
{
    return impl->window_;
}

void video_component::enable_wireframe(bool state)
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

void video_component::clean_up()
{
    if (impl->window_ != nullptr)
    {
        SDL_DestroyWindow(impl->window_);
    }

    SDL_Quit();
}

void video_component::render_light(const model&          model,
                                   const vec3&           light_position,
                                   const movable_object& camera)
{
    ptm::matrix4x4 translation_m = ptm::translation(light_position);

    glm::mat4 translate_m = glm_mat(translation_m);

    glm::mat4 view_m = get_view_matrix(camera);

    glm::mat4 full_transform_m = get_projection_matrix() * view_m * translate_m;

    impl->light_program_->use();

    impl->light_program_->set_vec3("u_color", { 1.0, 1.0, 1.0 });

    impl->light_program_->set_matrix4("u_transform_matrix",
                                      glm::value_ptr(full_transform_m));
    impl->light_program_->validate();

    // model.draw(*(impl->light_program_.get()));
    draw_model(model, *impl->light_program_);
}

void render_line_internal(const ptm::vec3& from, const ptm::vec3& to)
{
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    ///////////////////////////////////////////////////////////////////////////
    // generate buffers

    glGenVertexArrays(1, &VAO);
    check_gl_errors();

    glGenBuffers(1, &VBO);
    check_gl_errors();

    glGenBuffers(1, &EBO);
    check_gl_errors();

    /////////////////////////////// ///////////////////////////////////////////
    // bind buffers

    glBindVertexArray(VAO);
    check_gl_errors();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    check_gl_errors();

    const ptm::vec3 vertices[2] = { from, to };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0],
                 GL_STATIC_DRAW);
    check_gl_errors();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    check_gl_errors();

    const unsigned int indices[2] = { 0, 1 };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0],
                 GL_STATIC_DRAW);
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // setup attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    check_gl_errors();

    glEnableVertexAttribArray(0); // can we use name instead of a number?
    check_gl_errors();

    glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, nullptr);
    check_gl_errors();

    glBindVertexArray(0);
    check_gl_errors();
}

void video_component::render_line(const ptm::vec3& from, const ptm::vec3& to,
                                  const ptm::vec3&             color,
                                  const struct movable_object& camera)
{
    glm::mat4 view_m = get_view_matrix(camera);

    glm::mat4 full_transform_m = get_projection_matrix() * view_m;

    impl->light_program_->use();

    impl->light_program_->set_matrix4("u_transform_matrix",
                                      glm::value_ptr(full_transform_m));

    impl->light_program_->set_vec3("u_color", color);

    impl->light_program_->validate();

    render_line_internal(from, to);
}

void video_component::render_line_ndc(const ptm::vec3& from,
                                      const ptm::vec3& to,
                                      const ptm::vec3& color)
{
    glm::mat4 identity =
        glm::mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 full_transform_m = identity; // indentity matrix

    impl->light_program_->use();

    impl->light_program_->set_matrix4("u_transform_matrix",
                                      glm::value_ptr(full_transform_m));

    impl->light_program_->set_vec3("u_color", color);

    impl->light_program_->validate();

    render_line_internal(from, to);
}

vec2i video_component::get_window_size() const
{
    int w, h;

    SDL_GetWindowSize(impl->window_, &w, &h);

    return { w, h };
}

void video_component::on_window_resize(Sint32 w, Sint32 h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
}

video_component::~video_component()
{
    SDL_GL_DeleteContext(impl->gl_context_);
    SDL_DestroyWindow(impl->window_);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void video_component::lock_cursor(bool is_locked)
{
    if (is_locked)
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}
void video_component::generate_alpha()
{
    data_ = (GLubyte*)malloc(w_ * h_);

    for (size_t w_index = 0; w_index < w_; ++w_index)
    {
        for (size_t h_index = 0; h_index < h_; ++h_index)
        {
            data_[w_index * w_ + h_index] = (GLubyte)0;
        }
    }

    const float density = 0.1f;
    auto        count   = static_cast<int>(density * (w_ * h_));
    for (size_t index = 0; index < count; ++index)
    {
        int xrand = std::rand() % w_;
        int yrand = std::rand() % h_;

        data_[xrand * w_ + yrand] = (GLubyte)255;
    }
}

void video_component::init_alpha_texture()
{
    glGenTextures(1, &textureID);

    check_gl_errors();

    glBindTexture(GL_TEXTURE_2D, textureID);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w_, h_, 0, GL_RED, GL_UNSIGNED_BYTE,
                 data_);
    check_gl_errors();
}

void load_mesh_into_gpu(std::unique_ptr<mesh>& mesh_ptr)
{
    unsigned int VBO  = 0;
    unsigned int EBO  = 0;
    unsigned int VAO_ = 0;

    ///////////////////////////////////////////////////////////////////////////
    // generate buffers
    glGenVertexArrays(1, &VAO_);
    check_gl_errors();

    glGenBuffers(1, &VBO);
    check_gl_errors();

    glGenBuffers(1, &EBO);
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // bind buffers

    glBindVertexArray(VAO_);
    check_gl_errors();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    check_gl_errors();

    glBufferData(GL_ARRAY_BUFFER, mesh_ptr->vertices.size() * sizeof(vertex),
                 mesh_ptr->vertices.data(), GL_STATIC_DRAW);
    check_gl_errors();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    check_gl_errors();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 mesh_ptr->indices.size() * sizeof(unsigned int),
                 mesh_ptr->indices.data(), GL_STATIC_DRAW);
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // setup attributes

    // position
    glEnableVertexAttribArray(0); // can we use name instead of a number?
    check_gl_errors();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    check_gl_errors();

    // texture
    glEnableVertexAttribArray(1);
    check_gl_errors();

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void*)(sizeof(ptm::vec3)));
    check_gl_errors();

    // color
    glEnableVertexAttribArray(2);
    check_gl_errors();

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void*)(sizeof(ptm::vec3) + sizeof(ptm::vec2)));
    check_gl_errors();

    // normals
    glEnableVertexAttribArray(3);
    check_gl_errors();

    glVertexAttribPointer(
        3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
        (void*)(sizeof(ptm::vec3) + sizeof(ptm::vec2) + sizeof(ptm::vec3)));
    check_gl_errors();

    glBindVertexArray(0);
    check_gl_errors();

    std::unique_ptr<vertex_buffer> vertex_buffer_ptr(new vertex_buffer_opengl(VAO_));

    mesh_ptr->vertex_buffer_ptr = std::move(vertex_buffer_ptr);
}

void video_component::load_model_into_gpu(std::unique_ptr<model>& model_ptr)
{
    for (auto& mesh : model_ptr->get_meshes())
    {
        load_mesh_into_gpu(mesh);
    }
}

} // namespace pt