#include "draw_line_tests.hpp"

#include "image.hpp"
#include "point.hpp"
#include "point_array.hpp"

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
        .draw(make_triangle(tr1), blue)
        .draw(make_triangle(tr2), blue)
        .draw(make_triangle(tr3), blue)
        .draw(make_triangle(tr4), blue)
        .draw(make_triangle(tr5), blue)
        .draw(make_triangle(tr6), blue)
        .draw(make_triangle(tr7), blue)
        .draw(make_triangle(tr8), blue)
        .save("triangle.ppm");

    // 01 draw a single line

    // 02 draw a triangle with lines

    // 03 draw multiple random triangles

    // 04 draw multiple triangle using vertex buffer (VB) and index buffer (IB)

    // 05 draw interpolated triangle with filling

    // 06 draw textured triangle

    return EXIT_SUCCESS;
}