#include "image.h"
#include <memory>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // bla-bla-bla...
    u_int8_t const WIDTH  = 100;
    u_int8_t const HEIGHT = 50;

    auto img = std::make_unique<image>(WIDTH, HEIGHT);

    for (uint16_t x = 0; x < img->width(); ++x)
    {
        for (uint16_t y = 0; y < img->height(); ++y)
        {
            img->pixel(x, y) = {0, 255, 0};
        }
    }

    img->save("img_01.ppm");

    return EXIT_SUCCESS;
}
