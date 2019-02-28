#include "renderer_opengl.hpp"
#include "opengl_utils.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"

#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace pt
{

std::ostream& operator<<(std::ostream& out, const glm::vec4& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
    return out;
}

glm::vec3 glm_vec(const vec3 vector)
{
    return { vector.x, vector.y, vector.z };
}

glm::mat4x4 look_at(const vec3& position, const vec3& direction, const vec3& up)
{
    return glm::lookAt(glm_vec(position), glm_vec(position + direction),
                       glm_vec(up));
}

void renderer_opengl::update_transform_matrix(
    const transformation& transformation, const camera& camera)
{
    glm::vec3 trans_v =
        glm::vec3(transformation.position.x, transformation.position.y,
                  transformation.position.z);

    glm::mat4 translate_m = glm::translate(glm::mat4(), trans_v);

    glm::mat4 rotate_m =
        glm::rotate(glm::mat4(), transformation.rotation_angle,
                    glm::vec3(transformation.rotation_vector.x,
                              transformation.rotation_vector.y,
                              transformation.rotation_vector.z));

    glm::mat4 view_m =
        look_at(camera.get_position(), camera.get_direction(), camera.get_up());

    glm::mat4 project_m =
        glm::perspective<float>(glm::pi<float>() / 2, 4.f / 3, 0.1f, 10.0f);

    glm::mat4 full_transfom_m = project_m * view_m * translate_m * rotate_m;

    GLint transformLoc =
        glGetUniformLocation(gl_program_id_, "u_transform_matrix");
    check_gl_errors();

    if (transformLoc == -1)
    {
        throw std::runtime_error(
            "error: could not find attribute 'u_transform_matrix'");
    }

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
                       glm::value_ptr(full_transfom_m));
    check_gl_errors();
}

void renderer_opengl::draw_triangle(const transformation& transformation,
                                    const camera&         camera)
{
    update_transform_matrix(transformation, camera);

    validate_program();

    glActiveTexture(GL_TEXTURE0);
    check_gl_errors();

    glBindTexture(GL_TEXTURE_2D, texture_id_);
    check_gl_errors();

    glDrawElements(GL_TRIANGLES, indecies_count_, GL_UNSIGNED_INT, nullptr);
    check_gl_errors();
}

bool renderer_opengl::initialize(SDL_Window* window)
{
    using namespace std;

    renderer::initialize(window);

    initialize_gl_functions();

    set_opengl_version();

    if (!get_opengl_context())
    {
        return false;
    }

    shader vertex_shader("shader01.vert", GL_VERTEX_SHADER);

    shader fragment_shader("shader01.frag", GL_FRAGMENT_SHADER);

    gl_program_id_ = glCreateProgram();
    check_gl_errors();

    if (gl_program_id_ == 0)
    {
        cerr << "Failed to create gl program" << '\n';
        return false;
    }

    glAttachShader(gl_program_id_, vertex_shader.get_shader_id());
    check_gl_errors();

    glAttachShader(gl_program_id_, fragment_shader.get_shader_id());
    check_gl_errors();

    vertex_shader_id_ = vertex_shader.get_shader_id();

    glLinkProgram(gl_program_id_);
    check_gl_errors();

    GLint linked_status = 0;
    glGetProgramiv(gl_program_id_, GL_LINK_STATUS, &linked_status);

    if (linked_status == GL_FALSE)
    {
        GLint info_length = 0;
        glGetProgramiv(gl_program_id_, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        string info_log(static_cast<unsigned int>(info_length), ' ');
        glGetProgramInfoLog(gl_program_id_, info_length, nullptr,
                            info_log.data());
        check_gl_errors();

        cerr << "Error linking the program:" << '\n' << info_log.data();

        glDeleteProgram(gl_program_id_);
        check_gl_errors();

        return false;
    }

    glUseProgram(gl_program_id_);
    check_gl_errors();

    glEnable(GL_DEPTH_TEST);
    check_gl_errors();

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

bool renderer_opengl::get_opengl_context()
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

void renderer_opengl::validate_program()
{

    glValidateProgram(gl_program_id_);
    check_gl_errors();

    GLint validate_result = 0;
    glGetProgramiv(gl_program_id_, GL_VALIDATE_STATUS, &validate_result);
    check_gl_errors();

    if (validate_result == GL_FALSE)
    {
        GLint info_length = 0;

        glGetProgramiv(gl_program_id_, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        std::string error_message(static_cast<unsigned int>(info_length), ' ');

        glGetProgramInfoLog(gl_program_id_, info_length, nullptr,
                            error_message.data());
        check_gl_errors();

        throw std::runtime_error("Error: failed to validate the program:" +
                                 error_message);
    }
}

void renderer_opengl::load_model(const model& model)
{
    glGenVertexArrays(1, &VAO_);
    check_gl_errors();

    glBindVertexArray(VAO_);
    check_gl_errors();

    GLuint VBO;
    glGenBuffers(1, &VBO);
    check_gl_errors();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    check_gl_errors();

    glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(vertex),
                 model.vertices.data(), GL_STATIC_DRAW);
    check_gl_errors();

    // position attribute
    glEnableVertexAttribArray(0); // can we use name instead of a number?
    check_gl_errors();

    // TODO replace with reinterpret cast
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    check_gl_errors();

    // texture coordinates attribute (uv coords)
    glEnableVertexAttribArray(1);
    check_gl_errors();

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void*)(3 * sizeof(float)));
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // setting up EBO

    glGenBuffers(1, &EBO_);
    check_gl_errors();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    check_gl_errors();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 model.indices.size() * sizeof(unsigned int),
                 model.indices.data(), GL_STATIC_DRAW);

    indecies_count_ = static_cast<GLsizei>(model.indices.size());

    ///////////////////////////////////////////////////////////////////////////
    // loading texture

    glUseProgram(gl_program_id_);
    check_gl_errors();

    int texture_unit = 0;
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    check_gl_errors();

    glGenBuffers(1, &texture_id_);
    check_gl_errors();

    glBindTexture(GL_TEXTURE_2D, texture_id_);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    check_gl_errors();

    const auto& i = model.image;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(i.width()),
                 static_cast<GLsizei>(i.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 &i.get_data()[0]);
    check_gl_errors();

    //////////////////////////////////////
    // passing texture to the uniform

    int location = glGetUniformLocation(gl_program_id_, "u_texture");
    check_gl_errors();

    assert(-1 != location);

    // http://www.khronos.org/opengles/sdk/docs/man/xhtml/glUniform.xml
    glUniform1i(location, 0 + texture_unit);
    check_gl_errors();

    glEnable(GL_BLEND);
    check_gl_errors();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    check_gl_errors();
}

void renderer_opengl::load_tecture()
{
    // update texture uniform
}

} // namespace pt
