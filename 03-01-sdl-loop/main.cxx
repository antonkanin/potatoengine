#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>

void print_event(const std::string_view& key_name,
                 const std::string_view& event_type)
{
    std::cout << key_name << ' ' << event_type << '\n';
}

void process_input(const SDL_Event& event, const std::string_view event_type)
{
    using namespace std;

    switch (event.key.keysym.sym)
    {
        case SDLK_UP:
        {
            print_event("up", event_type);
            break;
        }
        case SDLK_RIGHT:
        {
            print_event("right", event_type);
            break;
        }
        case SDLK_DOWN:
        {
            print_event("down", event_type);
            break;
        }
        case SDLK_LEFT:
        {
            print_event("left", event_type);
            break;
        }
        case SDLK_q:
        {
            print_event("button_one", event_type);
            break;
        }
        case SDLK_w:
        {
            print_event("button_two", event_type);
            break;
        }
        case SDLK_1:
        {
            print_event("select", event_type);
            break;
        }
        case SDLK_2:
        {
            print_event("start", event_type);
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
                    process_input(event, "pressed");
                    break;
                }

                case SDL_KEYUP:
                {
                    process_input(event, "lifted");
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
