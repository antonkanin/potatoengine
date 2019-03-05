#include "opengl_utils.hpp"

#include <iostream>

PFNGLCREATESHADERPROC            glCreateShader            = nullptr;
PFNGLSHADERSOURCEPROC            glShaderSource            = nullptr;
PFNGLCOMPILESHADERPROC           glCompileShader           = nullptr;
PFNGLGETSHADERIVPROC             glGetShaderiv             = nullptr;
PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog        = nullptr;
PFNGLDELETESHADERPROC            glDeleteShader            = nullptr;
PFNGLCREATEPROGRAMPROC           glCreateProgram           = nullptr;
PFNGLATTACHSHADERPROC            glAttachShader            = nullptr;
PFNGLBINDATTRIBLOCATIONPROC      glBindAttribLocation      = nullptr;
PFNGLLINKPROGRAMPROC             glLinkProgram             = nullptr;
PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog       = nullptr;
PFNGLDELETEPROGRAMPROC           glDeleteProgram           = nullptr;
PFNGLUSEPROGRAMPROC              glUseProgram              = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC     glVertexAttribPointer     = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVALIDATEPROGRAMPROC         glValidateProgram         = nullptr;
PFNGLGETPROGRAMIVPROC            glGetProgramiv            = nullptr;
PFNGLGETATTRIBLOCATIONPROC       glGetAttribLocation       = nullptr;
PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation      = nullptr;
PFNGLUNIFORM1FPROC               glUniform1f               = nullptr;
PFNGLUNIFORM1IPROC               glUniform1i               = nullptr;
PFNGLUNIFORMMATRIX4FVPROC        glUniformMatrix4fv        = nullptr;
PFNGLGENBUFFERSPROC              glGenBuffers              = nullptr;
PFNGLBINDBUFFERPROC              glBindBuffer              = nullptr;
PFNGLBUFFERDATAPROC              glBufferData              = nullptr;
PFNGLGENVERTEXARRAYSPROC         glGenVertexArrays         = nullptr;
PFNGLBINDVERTEXARRAYPROC         glBindVertexArray         = nullptr;
PFNGLDETACHSHADERPROC            glDetachShader            = nullptr;
PFNGLBINDSAMPLERPROC             glBindSampler             = nullptr;
PFNGLDELETEBUFFERSPROC           glDeleteBuffers           = nullptr;
PFNGLDELETEVERTEXARRAYSPROC      glDeleteVertexArrays      = nullptr;
PFNGLBLENDEQUATIONSEPARATEPROC   glBlendEquationSeparate   = nullptr;
PFNGLBLENDFUNCSEPARATEPROC       glBlendFuncSeparate       = nullptr;

void set_opengl_version()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
}

void print_opengl_version()
{
    int major_version = 0;
    int minor_version = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);

    std::cout << "Using OpenGL version " << major_version << '.'
              << minor_version << std::endl;
}

void check_gl_errors()
{
    const GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        switch (error)
        {
            case GL_INVALID_ENUM:
            {
                std::cerr << "GL_INVALID_ENUM" << '\n';
                break;
            }

            case GL_INVALID_VALUE:
            {
                std::cerr << "GL_INVALID_VALUE" << '\n';
                break;
            }

            case GL_INVALID_OPERATION:
            {
                std::cerr << "GL_INVALID_OPERATION" << '\n';
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION:
            {
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << '\n';
                break;
            }

            case GL_OUT_OF_MEMORY:
            {
                std::cerr << "GL_OUT_OF_MEMORY" << '\n';
                break;
            }

            default:
            {
                std::cerr << "Unknown OpenGL error" << '\n';
                break;
            }
        }
    }
}

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
    load_gl_func("glGetUniformLocation", glGetUniformLocation);
    load_gl_func("glUniformMatrix4fv", glUniformMatrix4fv);
    load_gl_func("glGenBuffers", glGenBuffers);
    load_gl_func("glBindBuffer", glBindBuffer);
    load_gl_func("glBufferData", glBufferData);
    load_gl_func("glGenVertexArrays", glGenVertexArrays);
    load_gl_func("glBindVertexArray", glBindVertexArray);
    load_gl_func("glUniform1i", glUniform1i);
    load_gl_func("glDetachShader", glDetachShader);
    load_gl_func("glBindSampler", glBindSampler);
    load_gl_func("glDeleteVertexArrays", glDeleteVertexArrays);
    load_gl_func("glBlendEquationSeparate", glBlendEquationSeparate);
    load_gl_func("glBlendFuncSeparate", glBlendFuncSeparate);
}