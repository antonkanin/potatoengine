#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace std;

    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    const SDL_Window* window =
        SDL_CreateWindow("SDL Game Loop", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        // SDL_Log("Error: failed to ")

    }




    // main game loop
    SDL_Event event;

    bool game_running = true;

    while (game_running)
    {
        while (SDL_PollEvent(&event))
        {
        }
    }

    return EXIT_SUCCESS;
}
