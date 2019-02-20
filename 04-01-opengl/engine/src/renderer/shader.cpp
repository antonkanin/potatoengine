#include "shader.hpp"
#include "SDL2/SDL_opengl.h"
#include "opengl_utils.hpp"
#include <filesystem>
#include <iostream>

namespace pt
{

shader::shader(const std::string& file_name, const GLenum shader_type)
{
    auto shader_text = load_from_file(file_name);

    compile(shader_text, shader_type);
}

bool shader::compile(const std::string& shader_text, GLenum shader_type)
{
    using namespace std;

    shader_id_ = glCreateShader(shader_type);

    check_gl_errors();

    const GLchar* shader_src = shader_text.c_str();

    glShaderSource(shader_id_, 1, &shader_src, nullptr);

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

        cerr << "Error compiling shader: " << shader_text << message.data()
             << '\n';

        return false;
    }

    return true;
}

std::string shader::load_from_file(const std::string& file_name)
{
    using namespace std;

    // TODO might need to rework this... do we need to get abolute path?
    string path = filesystem::current_path().string() + "/" + file_name;

    fstream file(path);

    if (!file.is_open())
    {
        throw runtime_error("Error: failed to open the shader file " +
                            file_name);
    }

    string       line;
    stringstream shader_ss;

    while (getline(file, line))
    {
        shader_ss << line << '\n';
    }

    file.close();

    return shader_ss.str();
}

GLuint shader::get_shader_id() const
{
    return shader_id_;
}

} // namespace pt