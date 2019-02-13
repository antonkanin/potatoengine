#include "draw_line_tests.h"

#include <algorithm>
#include <array>
#include <memory>
#include <stdlib.h>
#include <iostream>



std::vector<point> move(std::vector<point>& points, const point& move_vector)
{
    for (auto& p : points)
    {
        p += move_vector;
    }

    return points;
}

// flips points array around the max Y value
point_array flip_y(const point_array& points)
{
    // fix max y
    auto max = std::max_element(
        begin(points), end(points),
        [](const point& p1, const point& p2) { return p1.x < p2.x; });

    point_array result;

    for (auto& p : points)
    {
        result.push_back(
            { static_cast<uint16_t>(p.x + 2 * (max->x - p.x)), p.y });
    }

    return result;
}

int main(int argc, char* argv[])
{
    // draw_line_tests(make_line_int);
    // draw_line_tests(make_line_float);

    // render_test_triangle();

    image img(20, 20);

    auto tr1 = point_array{ { 3, 1 }, { 1, 5 }, { 5, 8 } } + point(0, 0);
    auto tr2 = point_array{ { 1, 5 }, { 3, 1 }, { 5, 8 } } + point(6, 0);
    auto tr3 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(0, 9);
    auto tr4 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(6, 9);

    auto tr5 = flip_y(tr1) /*+ point(8, 0)*/;

    std::cout << tr1 << '\n';
    std::cout << tr5 << '\n';

    //    auto tr6 = point_array{ { 1, 5 }, { 3, 1 }, { 5, 8 } } + point(6, 0);
    //    auto tr7 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(0, 9);
    //    auto tr8 = point_array{ { 3, 1 }, { 5, 8 }, { 1, 5 } } + point(6, 9);

    img.fill(green)
        //        .draw(make_line_int({ 0, 0 }, {50, 0}), blue)
        //        .draw(make_line_int({ 0, 0 }, {0, 50}), blue)
        //        .draw(make_line_int({ 50, 0 }, {0, 50}), blue)
        .draw(make_triangle(tr1), blue)
//        .draw(make_triangle(tr2), blue)
//        .draw(make_triangle(tr3), blue)
//        .draw(make_triangle(tr4), blue)
        .draw(make_triangle(tr5), blue)
        //        .draw(make_triangle({ 9, 1 }, { 10, 5 }, { 7, 8 }), blue)
        //        .draw(make_triangle({ 3, 0 }, { 5, 0 }, { 4, 1 }), blue)
        //        .draw(make_triangle({ 0, 0 }, { 4, 0 }, { 0, 2 }), blue)
        //        .draw(make_triangle({ 4, 0 }, { 0, 0 }, { 2, 2 }), blue)
        //        draw(make_triangle({ 10, 10 }, { 40, 70 }, { 70, 40 }), blue)
        .save("triangle.ppm");

    return EXIT_SUCCESS;
}