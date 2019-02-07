#include "engine.h"

class engine_sdl : public engine
{
public:
    void init()
    {
        const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
        if (init_result != 0)
        {
            SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
            return EXIT_FAILURE;
        }

    }
};

