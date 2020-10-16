#include "game.hpp"
#include <ptexception.hpp>

int main()
{
    try
    {
        Game::runGame();
    }
    catch (const pt::PtException& exception)
    {
        pt::log_error(exception.message());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}