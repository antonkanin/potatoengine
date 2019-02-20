#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdexcept>
#include <string>

// TODO need to ask Sensei what the best way to declare 'locally public'
// function pointers?

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

template <typename T>
static void load_gl_func(const std::string& func_name, T& result)
{
    void* func_pointer = SDL_GL_GetProcAddress(func_name.data());
    if (func_pointer == nullptr)
    {
        throw std::runtime_error("Error: could not load OpenGL function: " +
                                 func_name);
    }

    auto t = reinterpret_cast<T>(func_pointer);;
    result = t;
}

void check_gl_errors();

void set_opengl_version();

void initialize_gl_functions();
