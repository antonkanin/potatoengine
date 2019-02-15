#include "draw_line_tests.hpp"
#include "image.hpp"
#include <utility>

void draw_line_tests(std::vector<point> (*make_line_func)(point, point))
{
    render_lines_list_test({ { { 0, 0 }, { 9, 9 } },
                             { { 0, 0 }, { 9, 4 } },
                             { { 0, 0 }, { 4, 9 } } },
                           "img_01.ppm", make_line_func);

    render_lines_list_test({ { { 0, 9 }, { 9, 0 } },
                             { { 0, 9 }, { 9, 4 } },
                             { { 0, 9 }, { 4, 0 } } },
                           "img_02.ppm", make_line_func);

    render_lines_list_test({ { { 9, 0 }, { 0, 9 } },
                             { { 9, 0 }, { 4, 9 } },
                             { { 9, 0 }, { 0, 4 } } },
                           "img_03.ppm", make_line_func);

    render_lines_list_test({ { { 9, 9 }, { 0, 0 } },
                             { { 9, 9 }, { 0, 4 } },
                             { { 9, 9 }, { 4, 0 } } },
                           "img_04.ppm", make_line_func);

    render_lines_list_test({ { { 1, 5 }, { 8, 8 } } }, "img_05.ppm",
                           make_line_func);
}

void render_lines_list_test(std::vector<std::pair<point, point>> lines,
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

void render_test_triangle()
{
    image img(10, 10);

    img.fill(green);

    auto triangle = make_solid_triangle({ 5, 0 }, { 1, 5 }, { 8, 8 });

    img.draw(triangle, blue);

    img.save("triangle_01.ppm");

    // render_line_test(make_line_int({ 5, 0 }, { 1, 5 }), "line_01.ppm");

    // debug
    render_lines_list_test({ { { 5, 0 }, { 1, 5 } },
                             { { 1, 5 }, { 8, 8 } },
                             { { 5, 0 }, { 8, 8 } } },
                           "line_01.ppm", make_line_int);
}

void render_line_test(const std::vector<point>& line,
                      const std::string&        image_name)
{
    image img(10, 10);

    img.fill(green);

    img.draw(line, blue);

    img.save(image_name);
}