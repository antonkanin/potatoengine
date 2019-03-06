#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdexcept>

extern PFNGLCREATESHADERPROC            glCreateShader;
extern PFNGLSHADERSOURCEPROC            glShaderSource;
extern PFNGLCOMPILESHADERPROC           glCompileShader;
extern PFNGLGETSHADERIVPROC             glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC            glDeleteShader;
extern PFNGLCREATEPROGRAMPROC           glCreateProgram;
extern PFNGLATTACHSHADERPROC            glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC      glBindAttribLocation;
extern PFNGLLINKPROGRAMPROC             glLinkProgram;
extern PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog;
extern PFNGLDELETEPROGRAMPROC           glDeleteProgram;
extern PFNGLUSEPROGRAMPROC              glUseProgram;
extern PFNGLVERTEXATTRIBPOINTERPROC     glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVALIDATEPROGRAMPROC         glValidateProgram;
extern PFNGLGETPROGRAMIVPROC            glGetProgramiv;
extern PFNGLGETATTRIBLOCATIONPROC       glGetAttribLocation;
extern PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation;
extern PFNGLUNIFORM1FPROC               glUniform1f;
extern PFNGLUNIFORM3FPROC               glUniform3f;
extern PFNGLUNIFORM1IPROC               glUniform1i;
extern PFNGLUNIFORMMATRIX4FVPROC        glUniformMatrix4fv;
extern PFNGLGENBUFFERSPROC              glGenBuffers;
extern PFNGLBINDBUFFERPROC              glBindBuffer;
extern PFNGLBUFFERDATAPROC              glBufferData;
extern PFNGLGENVERTEXARRAYSPROC         glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC         glBindVertexArray;
extern PFNGLDETACHSHADERPROC            glDetachShader;
extern PFNGLBINDSAMPLERPROC             glBindSampler;
extern PFNGLDELETEBUFFERSPROC           glDeleteBuffers;
extern PFNGLDELETEVERTEXARRAYSPROC      glDeleteVertexArrays;
extern PFNGLBLENDEQUATIONSEPARATEPROC   glBlendEquationSeparate;
extern PFNGLBLENDFUNCSEPARATEPROC       glBlendFuncSeparate;

template <typename T>
static void load_gl_func(const std::string& func_name, T& result)
{
    void* func_pointer = SDL_GL_GetProcAddress(func_name.data());

    if (func_pointer == nullptr)
    {
        throw std::runtime_error("Error: could not load OpenGL function: " +
                                 func_name);
    }

    result = reinterpret_cast<T>(func_pointer);
}

void check_gl_errors();

void set_opengl_version();

void print_opengl_version();

void initialize_gl_functions();
