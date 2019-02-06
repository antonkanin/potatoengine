#include <SDL2/SDL.h>
#include <iostream>

void process_input(const SDL_Event& event)
{
    using namespace std;

    switch (event.key.keysym.sym)
    {
        case SDLK_UP:
        {
            if (event.key.type == SDL_KEYUP)
            {
                cout << "UP lifted" << '\n';
            }
            else
            {
                cout << "UP pressed" << '\n';
            }
            break;
        }
        case SDLK_DOWN:
        {
            cout << "DOWN" << '\n';
            break;
        }

        default:
        {
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    using namespace std;

    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // TODO fix the warning "Warning:(47, 43) Clang-Tidy: Use of a signed
    // integer operand with a binary bitwise operator"
    SDL_Window* window =
        SDL_CreateWindow("SDL Game Loop", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        SDL_Log("Error: failed to SDL window %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    bool game_running = true;

    while (game_running)
    {
        // main game loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    process_input(event);
                    break;
                }

                case SDL_KEYUP:
                {
                    process_input(event);
                    break;
                }

                case SDL_QUIT:
                {
                    game_running = false;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
