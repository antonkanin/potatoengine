#include "shader.hpp"
#include "SDL2/SDL_opengl.h"
#include "opengl_utils.hpp"
#include <filesystem>
#include <iostream>

namespace pt
{

shader::shader(const std::string& file_name)
{
    using namespace std;

    //cout << filesystem::current_path() << endl;

    string path = filesystem::current_path().string() + "/" +  file_name;
    cout << path << endl;

    fstream file(path);


    if (!file.is_open())
    {
        throw runtime_error("Error: failed to open the shader file " +
                            file_name);
    }
}

bool shader::compile()
{
    using namespace std;

    shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);

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
    glShaderSource(shader_id_, 1, &src, nullptr);

    check_gl_errors();

    glCompileShader(shader_id_);

    check_gl_errors();

    GLint compilation_result;
    glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &compilation_result);

    check_gl_errors();

    if (compilation_result == GL_FALSE)
    {
        GLsizei error_length = 0;
        glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &error_length);

        check_gl_errors();

        string message(static_cast<unsigned int>(error_length), ' ');
        glGetShaderInfoLog(shader_id_, error_length, nullptr, message.data());

        check_gl_errors();

        glDeleteShader(shader_id_);

        cerr << "Error compiling fragment shader: " << fragment_shader_source
             << message.data() << '\n';

        return false;
    }

    return true;
}

} // namespace pt