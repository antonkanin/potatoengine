#include "draw_line_tests.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // draw_line_tests(make_line_int);
    // draw_line_tests(make_line_float);

    // render_test_triangle();

    image img(30, 30);

    auto tr1 = point_array{ { 3, 1 }, { 1, 5 }, { 5, 8 } } + point(0, 0);
    auto tr2 = point_array{ { 1, 5 }, { 3, 1 }, { 5, 8 } } + point(6, 0);
    auto tr3 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(0, 9);
    auto tr4 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(6, 9);

    auto tr5 = flip_y(tr1) + point(8, 0);
    auto tr6 = flip_y(tr2) + point(8, 0);
    auto tr7 = flip_y(tr3) + point(8, 0);
    auto tr8 = flip_y(tr4) + point(8, 0);

    img.fill(green)
        //        .draw(make_line_int({ 0, 0 }, { 50, 0 }), blue)
        //        .draw(make_line_int({ 0, 0 }, { 0, 50 }), blue)
        //        .draw(make_line_int({ 50, 0 }, { 0, 50 }), blue)
        .draw(make_triangle(tr1), blue)
        .draw(make_triangle(tr2), blue)
        .draw(make_triangle(tr3), blue)
        .draw(make_triangle(tr4), blue)
        .draw(make_triangle(tr5), blue)
        .draw(make_triangle(tr6), blue)
        .draw(make_triangle(tr7), blue)
        .draw(make_triangle(tr8), blue)
        //        .draw(make_triangle({ 9, 1 }, { 10, 5 }, { 7, 8 }), blue)
        //        .draw(make_triangle({ 3, 0 }, { 5, 0 }, { 4, 1 }), blue)
        //        .draw(make_triangle({ 0, 0 }, { 4, 0 }, { 0, 2 }), blue)
        //        .draw(make_triangle({ 4, 0 }, { 0, 0 }, { 2, 2 }), blue)
        //        draw(make_triangle({ 10, 10 }, { 40, 70 }, { 70, 40 }), blue)
        .save("triangle.ppm");

    return EXIT_SUCCESS;
}