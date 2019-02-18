#include "SDL_Loop.hpp"

#include "color.hpp"
#include "draw_utils.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include <SDL2/SDL.h>

SDL_Window* gWindow = nullptr;

SDL_Surface* screen_surface = nullptr;

SDL_Surface* image_surface = nullptr;

const int SCREEN_WIDTH  = 600;
const int SCREEN_HEIGHT = 400;

bool init()
{
    // Initialization flag
    bool success = true;
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    { // Create window
        gWindow = SDL_CreateWindow("2D Rendering demo (c) arm-ass studio", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
            success = false;
        }
        else
        { // Get window surface
            screen_surface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;
    // Load splash image
    image_surface = SDL_CreateRGBSurfaceWithFormat(
        0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);

    if (image_surface == nullptr)
    {
        SDL_Log("SDL_CreateRGBSurfaceWithFormat() failed: %s", SDL_GetError());
        exit(1);
    }

    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(image_surface);
    image_surface = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

void apply_bitmap(SDL_Surface* surface, const vertex_array& vertexes)
{
    for (const vertex& v : vertexes)
    {
        if (v.x >= 0 && v.y >= 0)
        {
            auto x = static_cast<uint16_t>(std::round(v.x));
            auto y = static_cast<uint16_t>(std::round(v.y));

            Uint32 pixel  = SDL_MapRGB(surface->format, v.c.r, v.c.g, v.c.b);
            auto   pixels = static_cast<Uint32*>(surface->pixels);
            pixels[y * surface->w + x] = pixel;
        }
    }
}

void SDL_loop()
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {

            vertex_array base_triangle = { { -100, 0, blue },
                                           { 0, -100, red },
                                           { 100, 100, yellow } };

            auto triangle      = base_triangle;
            auto triangle_mesh = draw_interpolated_triangle(
                base_triangle[0], base_triangle[1], base_triangle[2]);

            Uint64 now  = SDL_GetPerformanceCounter();
            Uint64 last = 0;

            double deltaTime = 0;
            double interval  = 0;

            double alpha = 0;

            bool game_running = true;

            while (game_running)
            {
                SDL_Event event;

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

                // getting deltaTime

                last = now;
                now  = SDL_GetPerformanceCounter();

                deltaTime = static_cast<double>(now - last) * 1000 /
                            static_cast<double>(SDL_GetPerformanceFrequency());

                interval += deltaTime;

                if (interval > 200)
                {
                    alpha += 3.14 / 15;

                    // cleaning the background by drawing black triangle

                    apply_fragment_shader(
                        triangle_mesh, [](const vertex& v) { return black; });

                    apply_bitmap(image_surface, triangle_mesh);

                    // initializing new triangle

                    triangle =
                        apply_vertex_shader(base_triangle, [&alpha](vertex& v) {
                            vertex out = v;

                            // rotation
                            out.x =
                                v.x * std::cos(alpha) - v.y * std::sin(alpha);
                            out.y =
                                v.x * std::sin(alpha) + v.y * std::cos(alpha);

                            // translation
                            out.x += 300;
                            out.y += 200;

                            return out;
                            // just adding 10 to the RED color, it will loop
                            // back to 0 once it reaches 255 since it's uint8
                            // v.c.b = static_cast<uint8_t>(v.c.b + 10);
                        });

                    triangle_mesh = draw_interpolated_triangle(
                        triangle[0], triangle[1], triangle[2]);

                    interval = 0;
                }

                // drawing on the screen
                apply_bitmap(image_surface, triangle_mesh);

                SDL_BlitSurface(image_surface, nullptr, screen_surface,
                                nullptr);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();
}