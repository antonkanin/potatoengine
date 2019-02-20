#include "shader.hpp"
#include "SDL2/SDL_opengl.h"
#include "opengl_utils.hpp"

namespace pt
{

shader::shader(const std::string& file_name)
{
    using namespace std;

    fstream file(file_name.data());
    if (!file.is_open())
    {
        throw runtime_error("error: failed to open the shader file " +
                            file_name);
    }
}

bool shader::compile()
{
    //    using namespace std;
    //
    //    shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
    //
    //    check_gl_errors();
    //
    //    string_view fragment_shader_source = R"(
    //        varying vec4 v_position;
    //        uniform float u_wave_value;
    //        void main()
    //        {
    //            float r = abs(v_position.x * 2.0);
    //            //float r = 0.0;
    //            float g = v_position.y * 2.0;
    //
    //            //float g = 1.0;
    //            float b = 0.0;
    //            gl_FragColor = vec4(r, g, b, 0);
    //        })";
    //
    //    // 06 glCreateProgram
    //
    //    const GLchar* src = fragment_shader_source.data();
    //    glShaderSource(fragment_shader_id, 1, &src, nullptr);
    //
    //    check_gl_errors();
    //
    //    glCompileShader(fragment_shader_id);
    //
    //    check_gl_errors();
    //
    //    GLint compilation_result;
    //    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS,
    //    &compilation_result);
    //
    //    check_gl_errors();
    //
    //    if (compilation_result == GL_FALSE)
    //    {
    //        GLsizei error_length = 0;
    //        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH,
    //        &error_length);
    //
    //        check_gl_errors();
    //
    //        string message(static_cast<unsigned int>(error_length), ' ');
    //        glGetShaderInfoLog(fragment_shader_id, error_length, nullptr,
    //                           message.data());
    //
    //        check_gl_errors();
    //
    //        glDeleteShader(fragment_shader_id);
    //
    //        cerr << "Error compiling fragment shader: " <<
    //        fragment_shader_source
    //             << message.data() << '\n';
    //
    //        return false;
    //    }
    //
    //    return true;

    return true;
}

} // namespace pt