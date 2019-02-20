#include "renderer_opengl.hpp"
#include "opengl_utils.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <iostream>

namespace pt
{


// TODO how can we move initialize_gl_functions() to a separate header?

void initialize_gl_functions()
{
    load_gl_func("glCreateShader", glCreateShader);
    load_gl_func("glShaderSource", glShaderSource);
    load_gl_func("glCompileShader", glCompileShader);
    load_gl_func("glGetShaderiv", glGetShaderiv);
    load_gl_func("glGetShaderInfoLog", glGetShaderInfoLog);
    load_gl_func("glDeleteShader", glDeleteShader);
    load_gl_func("glCreateProgram", glCreateProgram);
    load_gl_func("glAttachShader", glAttachShader);
    load_gl_func("glBindAttribLocation", glBindAttribLocation);
    load_gl_func("glLinkProgram", glLinkProgram);
    load_gl_func("glGetProgramiv", glGetProgramiv);
    load_gl_func("glGetProgramInfoLog", glGetProgramInfoLog);
    load_gl_func("glDeleteProgram", glDeleteProgram);
    load_gl_func("glUseProgram", glUseProgram);
    load_gl_func("glVertexAttribPointer", glVertexAttribPointer);
    load_gl_func("glEnableVertexAttribArray", glEnableVertexAttribArray);
    load_gl_func("glValidateProgram", glValidateProgram);
    load_gl_func("glGetAttribLocation", glGetAttribLocation);
}

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

        string error_message(static_cast<unsigned int>(info_length), ' ');

        glGetProgramInfoLog(gl_program_id, info_length, nullptr,
                            error_message.data());

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

    GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);

    check_gl_errors();

    // 02 load shader from the source code

    string_view vertex_shader_src = R"(
                                    attribute vec3 a_position;
                                    varying vec4 v_position;
                                    void main()
                                    {
                                    v_position = vec4(a_position, 1.0);
                                    gl_Position = v_position;
                                    }
                                    )";

    const GLchar* source = vertex_shader_src.data();
    glShaderSource(vert_shader_id, 1, &source, nullptr);

    check_gl_errors();

    // 03 compile shader glCompileShader

    glCompileShader(vert_shader_id);

    check_gl_errors();

    // 04 glGetShaderiv - check for compilation errors

    GLint compiled_status = 0;
    glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &compiled_status);

    check_gl_errors();

    // 05 look at compilation error details

    if (compiled_status == GL_FALSE)
    {
        GLint info_len = 0;

        glGetShaderiv(vert_shader_id, GL_INFO_LOG_LENGTH, &info_len);

        check_gl_errors();

        string info_details(static_cast<unsigned int>(info_len), ' ');
        glGetShaderInfoLog(vert_shader_id, info_len, nullptr,
                           info_details.data());

        check_gl_errors();

        // delete shader if it wasn't compiled correctly

        glDeleteShader(vert_shader_id);

        check_gl_errors();

        cerr << "Error compiling vertex shader: " << vertex_shader_src
             << info_details.data() << '\n';

        return false;
    }

    //  *** Repeat the same steps for fragment shader

    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    check_gl_errors();

    string_view fragment_shader_source = R"(
        varying vec4 v_position;
        uniform float u_wave_value;
        void main()
        {
            float r = abs(v_position.x * 2.0);
            //float r = 0.0;
            float g = v_position.y * 2.0;

            //float g = 1.0;
            float b = 0.0;
            gl_FragColor = vec4(r, g, b, 0);
        })";

    // 06 glCreateProgram

    const GLchar* src = fragment_shader_source.data();
    glShaderSource(fragment_shader_id, 1, &src, nullptr);

    check_gl_errors();

    glCompileShader(fragment_shader_id);

    check_gl_errors();

    GLint compilation_result;
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compilation_result);

    check_gl_errors();

    if (compilation_result == GL_FALSE)
    {
        GLsizei error_length = 0;
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &error_length);

        check_gl_errors();

        string message(static_cast<unsigned int>(error_length), ' ');
        glGetShaderInfoLog(fragment_shader_id, error_length, nullptr,
                           message.data());

        check_gl_errors();

        glDeleteShader(fragment_shader_id);

        cerr << "Error compiling fragment shader: " << fragment_shader_source
             << message.data() << '\n';

        return false;
    }

    // 07 Create program
    gl_program_id = glCreateProgram();

    check_gl_errors();

    if (gl_program_id == 0)
    {
        cerr << "Failed to create gl program" << '\n';
        return false;
    }

    // 07 glAttachShader - to attach shader to the program

    glAttachShader(gl_program_id, vert_shader_id);

    check_gl_errors();

    glAttachShader(gl_program_id, fragment_shader_id);

    check_gl_errors();

    // 08 binding attributes

    glBindAttribLocation(gl_program_id, 0, "a_position");

    check_gl_errors();

    // 09 link shaders program

    glLinkProgram(gl_program_id);

    check_gl_errors();

    // 10 check linking status

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