#include "renderer_opengl.hpp"
#include "opengl_utils.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"
#include <SDL2/SDL_opengl.h>
#include <iostream>

namespace pt
{

void renderer_opengl::draw_triangle(const triangle& tri)
{
    using namespace std;

    GLint position_attr = glGetAttribLocation(gl_program_id, "a_position");
    check_gl_errors();

    if (position_attr == -1)
    {
        throw runtime_error("error: could not find attribute 'a_position'");
    }

    glVertexAttribPointer(position_attr, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          &tri);
    check_gl_errors();

    glEnableVertexAttribArray(position_attr);
    check_gl_errors();

    glValidateProgram(gl_program_id);
    check_gl_errors();

    GLint validate_result = 0;
    glGetProgramiv(gl_program_id, GL_VALIDATE_STATUS, &validate_result);

    if (validate_result == GL_FALSE)
    {
        GLint info_length = 0;

        glGetProgramiv(gl_program_id, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        string error_message(static_cast<unsigned int>(info_length), ' ');

        glGetProgramInfoLog(gl_program_id, info_length, nullptr,
                            error_message.data());
        check_gl_errors();

        cerr << "Error linking the program:" << '\n' << error_message.data();

        throw runtime_error("error");
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);

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

    gl_program_id = glCreateProgram();
    check_gl_errors();

    if (gl_program_id == 0)
    {
        cerr << "Failed to create gl program" << '\n';
        return false;
    }

    glAttachShader(gl_program_id, vertex_shader.get_shader_id());
    check_gl_errors();

    glAttachShader(gl_program_id, fragment_shader.get_shader_id());
    check_gl_errors();

    glBindAttribLocation(gl_program_id, 0, "a_position");
    check_gl_errors();

    glLinkProgram(gl_program_id);
    check_gl_errors();

    GLint linked_status = 0;
    glGetProgramiv(gl_program_id, GL_LINK_STATUS, &linked_status);

    if (linked_status == GL_FALSE)
    {
        GLint info_length = 0;
        glGetProgramiv(gl_program_id, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        string info_log(static_cast<unsigned int>(info_length), ' ');
        glGetProgramInfoLog(gl_program_id, info_length, nullptr,
                            info_log.data());
        check_gl_errors();

        cerr << "Error linking the program:" << '\n' << info_log.data();

        glDeleteProgram(gl_program_id);
        check_gl_errors();

        return false;
    }

    glUseProgram(gl_program_id);
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
    gl_context = SDL_GL_CreateContext(window_);

    if (gl_context == nullptr)
    {
        std::cout << "error: count not create OpenGL context: "
                  << SDL_GetError() << '\n';
        return false;
    }

    SDL_assert(gl_context != nullptr);

    return true;
}

} // namespace pt