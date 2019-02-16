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

bool init()
{
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
            load_gl_function<PFNGLCOMPILESHADERPROC>("glCreateShader");


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

    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);



    // 02 load shader form the text string with glShaderSource

    // 03 glCompileShader

    // 04 glGetShaderiv - check for errors

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
