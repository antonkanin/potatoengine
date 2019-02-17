#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

SDL_Window*   sdl_window   = nullptr;
SDL_GLContext gl_context   = nullptr;
bool          game_running = true;

template <typename T>
T load_gl_function(const std::string name)
{
    return reinterpret_cast<T>(SDL_GL_GetProcAddress("glCreateShader"));
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
                std::cerr << "GL_INVALID_ENUM: An unacceptable value is "
                             "specified for an enumerated argument"
                          << '\n';
                break;
            }

            case GL_INVALID_VALUE:
            {
                std::cerr
                    << "GL_INVALID_VALUE: A numeric argument is out of range"
                    << '\n';
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

bool init()
{
    using namespace std;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "error: could not initialize SDL: " << SDL_GetError()
                  << '\n';
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////
    // Initialize window context

    const int WIDTH  = 800;
    const int HEIGHT = 600;

    sdl_window = SDL_CreateWindow("OpenGL sandbox", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                                  SDL_WINDOW_OPENGL);
    if (sdl_window == nullptr)
    {
        std::cout << "error: could not create window: " << SDL_GetError()
                  << '\n';
        SDL_Quit();
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////
    // Set OpenGL version & flags

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    /////////////////////////////////////////////////////////////////////////////////
    // Get OpenGL context

    gl_context = SDL_GL_CreateContext(sdl_window);

    if (gl_context == nullptr)
    {
        std::cout << "error: count not create OpenGL context: "
                  << SDL_GetError() << '\n';
        return false;
    }
    SDL_assert(gl_context != nullptr);

    /////////////////////////////////////////////////////////////////////////////////
    // Initialize OpenGL API functions that we are going to use

    auto glCreateShader =
        load_gl_function<PFNGLCREATESHADERPROC>("glCreateShader");

    auto glShaderSource =
        load_gl_function<PFNGLSHADERSOURCEPROC>("glCreateShader");

    auto glCompileShader =
        load_gl_function<PFNGLCOMPILESHADERPROC>("glCompileShader");

    auto glGetShaderiv =
        load_gl_function<PFNGLGETSHADERIVPROC>("glGetShaderiv");

    auto glGetShaderInfoLog =
        load_gl_function<PFNGLGETSHADERINFOLOGPROC>("glGetShaderInfoLog");

    auto glDeleteShader =
        load_gl_function<PFNGLDELETESHADERPROC>("glDeleteShader");

    //    "glCreateShader", glCreateShader);
    //    "glShaderSource", glShaderSource);
    //    "glCompileShader", glCompileShader);
    //    "glGetShaderiv", glGetShaderiv);
    //    "glGetShaderInfoLog", glGetShaderInfoLog);
    //    "glDeleteShader", glDeleteShader);

    //    "glCreateProgram", glCreateProgram);
    //    "glAttachShader", glAttachShader);
    //    "glBindAttribLocation", glBindAttribLocation);
    //    "glLinkProgram", glLinkProgram);
    //    "glGetProgramiv", glGetProgramiv);
    //    "glGetProgramInfoLog", glGetProgramInfoLog);
    //    "glDeleteProgram", glDeleteProgram);
    //    "glUseProgram", glUseProgram);
    //    "glVertexAttribPointer", glVertexAttribPointer);
    //    "glEnableVertexAttribArray", glEnableVertexAttribArray);
    //    "glValidateProgram", glValidateProgram);

    // 01 create shader with glCreateShader

    GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);

    check_gl_errors();

    // 02 load shader from the source code

    const char* vertex_shader_src = R"(
                                    attribute vec3 a_position;
                                    varying vec4 v_position;
                                    void main()
                                    {
                                    v_position = vec4(a_position, 1.0);
                                    gl_Position = v_position;
                                    }
                                    )";

    glShaderSource(vert_shader_id, 1, &vertex_shader_src, nullptr);

    check_gl_errors();

    // 03 compile shader glCompileShader

    glCompileShader(vert_shader_id);

    check_gl_errors();

    // 04 glGetShaderiv - check for compilation errors

    GLint compiled_status = 0;
    glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &compiled_status);

    check_gl_errors();

    // 05 look at compilation error details

    if (compiled_status == 0)
    {
        GLint info_len = 0;

        glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &info_len);

        check_gl_errors();

        GLchar* info_details = nullptr;
        glGetShaderInfoLog(vert_shader_id, info_len, nullptr, info_details);

        check_gl_errors();

        // delete shader if it wasn't compiled correctly

        glDeleteShader(vert_shader_id);

        check_gl_errors();

        cerr << "Error compiling vertex shader: " << vertex_shader_src << info_details << '\n';

        return false;
    }

    //      05 glGetShaderInfoLog - get error detaill

    //      06 glDeleteShader - clean up the shader

    //  *** Repeat the same steps for fragment shader

    // 06 glCreateProgram

    // 07 glAttachShader - to attach shader to the program

    // 08 glBindAttribLocation

    // 09 glLinkProgram

    // 10 glUseProgram

    return true;
}

SDL_Event event;

void process_events()
{
    if (SDL_PollEvent(&event))
    {
        /* an event was found */
        switch (event.type)
        {
            /* close button clicked */
            case SDL_QUIT:
            {
                game_running = false;
                break;
            }

                /* handle the keyboard */
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        game_running = false;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
        }
    }
}

void render() {}

int main(int /*argc*/, char** /*argv*/)
{
    if (!init())
    {
        return EXIT_FAILURE;
    }

    while (game_running)
    {
        process_events();

        render();

        SDL_GL_SwapWindow(sdl_window);
    }

    return EXIT_SUCCESS;
}
