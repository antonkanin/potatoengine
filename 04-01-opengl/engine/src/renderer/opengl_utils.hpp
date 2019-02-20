#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdexcept>
#include <string>

// TODO need to ask Sensei what the best way to declare 'locally public'
// function pointers?

static PFNGLCREATESHADERPROC            glCreateShader            = nullptr;
static PFNGLSHADERSOURCEPROC            glShaderSource            = nullptr;
static PFNGLCOMPILESHADERPROC           glCompileShader           = nullptr;
static PFNGLGETSHADERIVPROC             glGetShaderiv             = nullptr;
static PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog        = nullptr;
static PFNGLDELETESHADERPROC            glDeleteShader            = nullptr;
static PFNGLCREATEPROGRAMPROC           glCreateProgram           = nullptr;
static PFNGLATTACHSHADERPROC            glAttachShader            = nullptr;
static PFNGLBINDATTRIBLOCATIONPROC      glBindAttribLocation      = nullptr;
static PFNGLLINKPROGRAMPROC             glLinkProgram             = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog       = nullptr;
static PFNGLDELETEPROGRAMPROC           glDeleteProgram           = nullptr;
static PFNGLUSEPROGRAMPROC              glUseProgram              = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC     glVertexAttribPointer     = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
static PFNGLVALIDATEPROGRAMPROC         glValidateProgram         = nullptr;
static PFNGLGETPROGRAMIVPROC            glGetProgramiv            = nullptr;
static PFNGLGETATTRIBLOCATIONPROC       glGetAttribLocation       = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC      glGetUniformLocation      = nullptr;
static PFNGLUNIFORM1FPROC               glUniform1f               = nullptr;

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

void initialize_gl_functions();

void check_gl_errors();

void set_opengl_version();