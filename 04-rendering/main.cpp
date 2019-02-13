#include "draw_line_tests.hpp"

#include "image.hpp"
#include "point.hpp"
#include "point_array.hpp"
#include <cstdlib>

int main(int argc, char* argv[])
{
    // draw_line_tests(make_line_int);
    // draw_line_tests(make_line_float);

    // render_test_triangle();

    //    image img(100, 100);
    //
    //    auto tr1 = point_array{ { 3, 1 }, { 1, 5 }, { 5, 8 } } + point(0, 0);
    //    auto tr2 = point_array{ { 1, 5 }, { 3, 1 }, { 5, 8 } } + point(6, 0);
    //    auto tr3 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(0, 9);
    //    auto tr4 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(6, 9);
    //
    //    auto tr5 = flip_y(tr1) + point(8, 0);
    //    auto tr6 = flip_y(tr2) + point(8, 0);
    //    auto tr7 = flip_y(tr3) + point(8, 0);
    //    auto tr8 = flip_y(tr4) + point(8, 0);
    //
    //    img.fill(white)
    //        .draw(make_triangle(tr1), blue)
    //        .draw(make_triangle(tr2), blue)
    //        .draw(make_triangle(tr3), blue)
    //        .draw(make_triangle(tr4), blue)
    //        .draw(make_triangle(tr5), blue)
    //        .draw(make_triangle(tr6), blue)
    //        .draw(make_triangle(tr7), blue)
    //        .draw(make_triangle(tr8), blue)
    //        .save("triangle.ppm");

    ///////////////////////////////////////////////////////////////////////////
    // 01 draw a single line

    //    img.fill(white)
    //        .draw(make_line_int({ 10, 10 }, { 90, 90 }), black)
    //        .save("01_line.ppm");

    ///////////////////////////////////////////////////////////////////////////
    // 02 draw a triangle with lines

    //    img.fill(white)
    //        .draw(make_triangle({ 10, 10 }, { 90, 90 }, { 30, 60 }), black)
    //        .save("02_triangle.ppm");

    ///////////////////////////////////////////////////////////////////////////
    // 03 draw multiple random triangles

    image img03;

    img03.fill(white);

    for (uint8_t counter = 0; counter < 10; ++counter)
    {
        point_array points;

        for (uint8_t v_index = 0; v_index < 3; ++v_index)
        {
            auto x = static_cast<uint8_t>(random() % img.width());
            auto y = static_cast<uint8_t>(random() % img.height());

            points.push_back({ x, y });
        }

        color clr = { static_cast<uint8_t>(random() % 255),
                      static_cast<uint8_t>(random() % 255),
                      static_cast<uint8_t>(random() % 255) };

        auto ln1 = make_line_int(points[0], points[1]);
        auto ln2 = make_line_int(points[1], points[2]);
        auto ln3 = make_line_int(points[2], points[0]);

        img.draw(ln1, clr);
        img.draw(ln2, clr);
        img.draw(ln3, clr);
    }

    img.save("03_random_triangles.ppm");

    ///////////////////////////////////////////////////////////////////////////
    // 04 draw multiple triangle using vertex buffer (VB) and index buffer (IB)

    // TODO ...

    ///////////////////////////////////////////////////////////////////////////
    // 05 draw interpolated triangle with filling

    // TODO ...

    // 06 draw textured triangle

    // TODO ...

    return EXIT_SUCCESS;
}