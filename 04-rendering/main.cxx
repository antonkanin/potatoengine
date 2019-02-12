#include "draw_line_tests.h"

#include <array>
#include <memory>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // draw_line_tests(make_line_int);
    // draw_line_tests(make_line_float);

    // render_test_triangle();

    image img(5, 5);

    img.fill(green)
//        .draw(make_line_int({ 0, 0 }, {50, 0}), blue)
//        .draw(make_line_int({ 0, 0 }, {0, 50}), blue)
//        .draw(make_line_int({ 50, 0 }, {0, 50}), blue)
        .draw(make_triangle({ 0, 0 }, { 2, 0 }, { 1, 1 }), blue)
//        .draw(make_triangle({ 3, 0 }, { 5, 0 }, { 4, 1 }), blue)
//        .draw(make_triangle({ 0, 0 }, { 4, 0 }, { 0, 2 }), blue)
        //.draw(make_triangle({ 4, 0 }, { 0, 0 }, { 2, 2 }), blue)
        //draw(make_triangle({ 10, 10 }, { 40, 70 }, { 70, 40 }), blue)
        .save("triangle.ppm");


    return EXIT_SUCCESS;
}