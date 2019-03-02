#include "shader.hpp"
#include "SDL2/SDL_opengl.h"
#include "opengl_utils.hpp"
#include <iostream>
#include <sstream>

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

    fstream file(file_name);

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

shader::~shader()
{
    glDeleteShader(shader_id_);
    check_gl_errors();
}

std::string shader_new::load_file(const std::string& file_name)
{
    std::fstream file(file_name);

    if (!file.is_open())
    {
        throw std::runtime_error("Error: failed to open the file" + file_name);
    }

    std::stringstream ss;

    ss << file.rdbuf();

    file.close();

    return ss.str();
}

GLuint shader_new::load_shader(const std::string& code, GLenum shader_type)
{

    GLuint shader_id;
    shader_id = glCreateShader(shader_type);
    check_gl_errors();

    glShaderSource(shader_id, 1,
                   reinterpret_cast<const GLchar* const*>(code.c_str()),
                   nullptr);
    check_gl_errors();

    GLint compilation_result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_result);
    check_gl_errors();

    if (GL_FALSE == compilation_result)
    {
        GLsizei error_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &error_length);

        check_gl_errors();

        std::string message(static_cast<unsigned int>(error_length), ' ');
        glGetShaderInfoLog(shader_id, error_length, nullptr, message.data());
        check_gl_errors();

        delete_shader(shader_id);

        std::cerr << "Error compiling shader: " << code << message.data()
                  << '\n';

        throw std::runtime_error("Error: failed to compile shader");
    }

    return shader_id;
}

shader_new::shader_new(const std::string& vertex_path,
                       const std::string& fragment_path)
{
    auto vertex_code = load_file(vertex_path);
    auto frag_code   = load_file(fragment_path);

    auto vertex_id = load_shader(vertex_code, GL_VERTEX_SHADER);
    auto frag_id   = load_shader(frag_code, GL_FRAGMENT_SHADER);

    program_id_ = make_program(vertex_id, frag_id);

    delete_shader(vertex_id);
    delete_shader(frag_id);
}

GLuint shader_new::make_program(GLuint vertex_id, GLuint fragment_id)
{
    GLuint result_program = glCreateProgram();
    check_gl_errors();

    glAttachShader(result_program, vertex_id);
    check_gl_errors();

    glAttachShader(result_program, fragment_id);
    check_gl_errors();

    glLinkProgram(result_program);
    check_gl_errors();

    GLint link_result;
    glGetProgramiv(result_program, GL_LINK_STATUS, &link_result);
    check_gl_errors();

    if (link_result == GL_FALSE)
    {
        GLint info_length = 0;
        glGetProgramiv(result_program, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        std::string info_log(static_cast<unsigned int>(info_length), ' ');
        glGetProgramInfoLog(result_program, info_length, nullptr,
                            info_log.data());
        check_gl_errors();

        std::cerr << "Error linking the program:" << '\n' << info_log.data();

        glDeleteProgram(result_program);
        check_gl_errors();

        throw std::runtime_error("Error: failed to link the program");
    }

    return result_program;
}

void shader_new::delete_shader(GLuint shader_id)
{
    glDeleteShader(shader_id);
    check_gl_errors();
}

void shader_new::use()
{
    glUseProgram(program_id_);
    check_gl_errors();
}

shader_new::~shader_new()
{
    glDeleteProgram(program_id_);
    check_gl_errors();
}

} // namespace pt