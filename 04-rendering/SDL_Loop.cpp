#include "SDL_Loop.hpp"

#include "color.hpp"
#include "draw_utils.hpp"
#include "vertex.hpp"
#include <SDL2/SDL.h>
#include <iostream>

// The window we'll be rendering to

SDL_Window* gWindow = NULL;

// The surface contained by the window

SDL_Surface* gScreenSurface = NULL;

// The image we will load and show on the screen

SDL_Surface* gHelloWorld = NULL;

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
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
            success = false;
        }
        else
        { // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;
    // Load splash image
    gHelloWorld =
        SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");

    gHelloWorld = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT,
                                                 32, SDL_PIXELFORMAT_RGBA32);

    if (gHelloWorld == nullptr)
    {
        SDL_Log("SDL_CreateRGBSurfaceWithFormat() failed: %s", SDL_GetError());
        exit(1);
    }

    return success;
}

void close()
{
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
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
        { // Apply the image
            float x_position = 20;
            auto triangle = draw_interpolated_triangle(
                    { 200, 0, blue }, { x_position, 200, red }, { 400, 400, yellow });

            Uint64 now       = SDL_GetPerformanceCounter();
            Uint64 last      = 0;
            double deltaTime = 0;

            double interval = 0;

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

                //

                interval += deltaTime;

                //std::cout << interval << '\n';

                if (interval > 500)
                {
                    x_position -= 1;
                    triangle = draw_interpolated_triangle(
                            { 200, 0, blue }, { x_position, 200, red }, { 400, 400, yellow });

                    std::cout << "drawing triangle at" << x_position << '\n';

                    interval = 0;
                }

                // drawing on the screen

                for (const vertex& v : triangle)
                {
                    auto x = static_cast<uint16_t>(std::round(v.x));
                    auto y = static_cast<uint16_t>(std::round(v.y));

                    Uint32 pixel =
                        SDL_MapRGB(gHelloWorld->format, v.c.r, v.c.g, v.c.b);
                    auto pixels = static_cast<Uint32*>(gHelloWorld->pixels);
                    pixels[y * gHelloWorld->w + x] = pixel;
                }

                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();
}