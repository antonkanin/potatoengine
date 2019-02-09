#include "image.h"
#include <memory>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // bla-bla-bla...
    u_int8_t const WIDTH  = 100;
    u_int8_t const HEIGHT = 50;

    auto img = std::make_unique<image>(WIDTH, HEIGHT);

    return EXIT_SUCCESS;
}
