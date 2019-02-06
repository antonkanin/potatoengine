#include <iostream>
#include <SDL2/SDL_version.h>

int main(int argc, char* argv[])
{
    using namespace std;

    SDL_version version = { 0, 0, 0};

    SDL_GetVersion(&version);

    cout << "SDL version: " << version.minor << "." << version.minor << "." << version.patch << "\n";

    return EXIT_SUCCESS;
}
