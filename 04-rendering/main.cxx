#include "draw_line_tests.h"
#include <array>
#include <memory>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    draw_line_tests(make_line_int);
    // draw_line_tests(make_line_float);

    return EXIT_SUCCESS;
}