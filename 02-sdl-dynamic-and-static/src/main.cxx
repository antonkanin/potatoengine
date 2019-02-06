#include <SDL2/SDL_version.h>
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace std;

    SDL_version version = { 0, 0, 0 };

    SDL_GetVersion(&version);

    cout << "SDL version: " << static_cast<int>(version.major) << "."
         << static_cast<int>(version.minor) << "."
         << static_cast<int>(version.patch) << "\n";

    return EXIT_SUCCESS;
}
