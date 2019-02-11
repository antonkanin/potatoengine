#pragma once

#include "draw_utils.h"

void draw_test_image(std::vector<std::pair<point, point>> lines,
                     const std::string&                   image_name,
                     std::vector<point> (*make_line_func)(point, point))
{
    const u_int8_t WIDTH  = 10;
    const u_int8_t HEIGHT = 10;

    image img(WIDTH, HEIGHT);

    img.fill(green);

    for (const auto& line : lines)
    {
        img.draw(make_line_func(line.first, line.second), blue);
    }

    img.save(image_name);
}

void draw_line_tests(std::vector<point> (*make_line_func)(point, point))
{
    draw_test_image({ { { 0, 0 }, { 9, 9 } },
                      { { 0, 0 }, { 9, 4 } },
                      { { 0, 0 }, { 4, 9 } } },
                    "img_01.ppm", make_line_func);

    draw_test_image({ { { 0, 9 }, { 9, 0 } },
                      { { 0, 9 }, { 9, 4 } },
                      { { 0, 9 }, { 4, 0 } } },
                    "img_02.ppm", make_line_func);

    draw_test_image({ { { 9, 0 }, { 0, 9 } },
                      { { 9, 0 }, { 4, 9 } },
                      { { 9, 0 }, { 0, 4 } } },
                    "img_03.ppm", make_line_func);

    draw_test_image({ { { 9, 9 }, { 0, 0 } },
                      { { 9, 9 }, { 0, 4 } },
                      { { 9, 9 }, { 4, 0 } } },
                    "img_04.ppm", make_line_func);
}

void draw_triangle_test()
{
    image img(10, 10);

    img.fill(green);

    auto triangle = make_triangle({5, 0}, {1, 5}, {8, 8});

    img.draw(triangle, blue);

    img.save("triangle_01.ppm");
}

