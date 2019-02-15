#include "SDL_Loop.hpp"

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
                                                 32, SDL_PIXELFORMAT_RGB24);

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
            for (int x = 0; x < 50; ++x)
            {
                for (int y = 0; y < 50; ++y)
                {

                    Uint8 r = 125;
                    Uint8 g = 0;
                    Uint8 b = 125;
                    //                    SDL_GetRGB(pixel, gHelloWorld->format,
                    //                    &r, &g, &b);

                    Uint32 pixel  = SDL_MapRGB(gHelloWorld->format, r, g, b);
                    auto   pixels = static_cast<Uint32*>(gHelloWorld->pixels);
                    pixels[y * gHelloWorld->w + x] = pixel;

                    // std::cout << "r: " << r << ", g: " << g << ", b: " << b
                    // << std::endl;
                }
            }

            SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);
            SDL_UpdateWindowSurface(gWindow);
            // Wait two seconds
            SDL_Delay(5000);
        }
    }

    close();
}