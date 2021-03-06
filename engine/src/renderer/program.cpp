#include "program.hpp"

#include "log_utils.hpp"
#include "opengl_utils.hpp"
#include "shader.hpp"

#include <ptm/vec3.hpp>

namespace pt
{

program::program(const std::string& vertex_path,
                 const std::string& fragment_path)
{
    shader vertex_shader(vertex_path, GL_VERTEX_SHADER);
    shader fragment_shader(fragment_path, GL_FRAGMENT_SHADER);

    program_id_ = make_program(vertex_shader.get_shader_id(),
                               fragment_shader.get_shader_id());
}

GLuint program::make_program(GLuint vertex_id, GLuint fragment_id)
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

        log_error("Error linking the program:\n" +
                  std::string(info_log.data()));

        glDeleteProgram(result_program);
        check_gl_errors();

        throw std::runtime_error("Error: failed to link the program");
    }

    return result_program;
}

void program::use()
{
    glUseProgram(program_id_);
    check_gl_errors();
}

program::~program()
{
    glDeleteProgram(program_id_);
    check_gl_errors();
}

void program::validate()
{

    glValidateProgram(program_id_);
    check_gl_errors();

    GLint validate_result = 0;
    glGetProgramiv(program_id_, GL_VALIDATE_STATUS, &validate_result);
    check_gl_errors();

    if (validate_result == GL_FALSE)
    {
        GLint info_length = 0;

        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        std::string error_message(static_cast<unsigned int>(info_length), ' ');

        glGetProgramInfoLog(program_id_, info_length, nullptr,
                            error_message.data());
        check_gl_errors();

        throw std::runtime_error("Error: failed to validate the program:" +
                                 error_message);
    }
}

void program::set_matrix4(const std::string& uniform_name,
                          const GLfloat*     uniform_value)
{
    GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
    check_gl_errors();

    if (-1 == location)
    {
        //        throw std::runtime_error("Error: could not find attribute " +
        //                                 uniform_name);
        log_error("Error: could not find matrix4 attribute " + uniform_name);
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, uniform_value);
    check_gl_errors();
}

bool program::set_1i(const std::string& uniform_name, GLint uniform_value)
{
    GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
    check_gl_errors();

    if (-1 == location)
    {
        //        throw std::runtime_error("Error: could not find attribute " +
        //                                 uniform_name);
        log_error("Error: could not find attribute " + uniform_name);
        return false;
    }

    glUniform1i(location, uniform_value);
    check_gl_errors();
    return true;
}

bool program::set_1f(const std::string& uniform_name, GLfloat uniform_value)
{
    GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
    check_gl_errors();

    if (-1 == location)
    {
        //        throw std::runtime_error("Error: could not find attribute " +
        //                                 uniform_name);
        log_line("Error: could not find attribute " + uniform_name);
        return false;
    }

    glUniform1f(location, uniform_value);
    check_gl_errors();
    return true;
}

void program::set_vec3(const std::string& uniform_name, ptm::vec3 value)
{
    GLint location = glGetUniformLocation(program_id_, uniform_name.c_str());
    check_gl_errors();

    if (-1 == location)
    {
        /*
                throw std::runtime_error("Error: could not find attribute " +
                                         uniform_name);
        */
        log_line("Error: could not find 3f attribute " + uniform_name);
        return;
    }

    glUniform3f(location, value.x, value.y, value.z);
    check_gl_errors();
}

GLuint program::id() const
{
    return program_id_;
}

} // namespace pt