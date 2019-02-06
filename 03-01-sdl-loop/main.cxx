#include <iostream>
#include <SDL2/SDL_events.h>

int main(int argc, int* argv[])
{
    using namespace std;

    cout << "Test" << endl;

    bool game_running = true;

    // main game loop
    SDL_Event event;

    while(game_running)
    {
        while (SDL_PollEvent(event))
        {

        }




    }


    return EXIT_SUCCESS;
}



