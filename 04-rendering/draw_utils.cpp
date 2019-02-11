#include "draw_utils.h"
#include "draw_line_tests.h"
#include <algorithm>

std::vector<point> make_line_float(point p1, point p2)
{
    std::vector<point> result;

    bool steep = false;
    if (abs(p2.y - p1.y) > abs(p2.x - p1.x))
    {
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        steep = true;
    }

    // this is a hack to make sure the returned line is not swapped
    bool is_reversed = false;
    if (p2.y < p1.y)
    {
        swap(p1, p2);
        is_reversed = true;
    }

    const float dydx = std::abs(static_cast<float>(p2.y - p1.y) /
                                static_cast<float>(p2.x - p1.x));

    if (p1.x <= p2.x)
    {
        auto x = p1.x;
        auto y = p1.y;

        float error = 0;

        while (x <= p2.x)
        {
            if (steep)
            {
                result.push_back({ y, x });
            }
            else
            {
                result.push_back({ x, y });
            }

            ++x;

            error += dydx;

            if (error > 0.5)
            {
                ++y;
                error -= 1.0;
            }
        }
    }
    else
    {
        auto x = p1.x;
        auto y = p1.y;

        float error = 0;

        while (x >= p2.x)
        {
            if (steep)
            {
                result.push_back({ y, x });
            }
            else
            {
                result.push_back({ x, y });
            }

            if (x == 0) // we have to this since we avoid 'overflow' for the
                        // unsigned int
            {
                break;
            }

            --x;

            error += dydx;

            if (error > 0.5)
            {
                ++y;
                error -= 1.0;
            }
        }
    }

    if (is_reversed)
    {
        std::reverse(begin(result), end(result));
    }

    return result;
}

std::vector<point> make_line_int(point p1, point p2)
{
    std::vector<point> result;

    bool steep = false;
    if (abs(p2.y - p1.y) > abs(p2.x - p1.x))
    {
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        steep = true;
    }

    bool is_reversed = false;
    if (p2.y < p1.y)
    {
        swap(p1, p2);
        is_reversed = true;
    }

    const auto dy = std::abs(p2.y - p1.y);
    const auto dx = std::abs(p2.x - p1.x);

    if (p1.x <= p2.x)
    {
        auto x = p1.x;
        auto y = p1.y;

        uint16_t error = 0;

        while (x <= p2.x)
        {
            if (steep)
            {
                result.push_back({ y, x });
            }
            else
            {
                result.push_back({ x, y });
            }

            ++x;

            error += dy;

            if (2 * error > dx)
            {
                ++y;
                error -= dx;
            }
        }
    }
    else
    {
        auto x = p1.x;
        auto y = p1.y;

        int16_t error = 0;

        while (x >= p2.x)
        {
            if (steep)
            {
                result.push_back({ y, x });
            }
            else
            {
                result.push_back({ x, y });
            }

            if (x == 0) // we have to this since we avoid 'overflow' for the
                        // unsigned int
            {
                break;
            }

            --x;

            error += dy;

            if (2 * error > dx)
            {
                ++y;
                error -= dx;
            }
        }
    }

    if (is_reversed)
    {
        std::reverse(begin(result), end(result));
    }

    return result;
}

std::vector<point> make_triangle(point p1, point p2, point p3)
{
    std::vector<point> result;

    // sorting vertexes
    std::vector<point> tr = { p1, p2, p3 };
    std::sort(begin(tr), end(tr),
              [](const point& p1_, const point& p2_) { return p1_.y < p2_.y; });
    p1 = tr[0];
    p2 = tr[1];
    p3 = tr[2];

    auto l1 = make_line_int(p1, p2);
    auto l2 = make_line_int(p1, p3);

    for (uint16_t ind = 0; ind <= (p2.y - p1.y); ++ind)
    {
        const uint16_t y = p1.y + ind;

        for (uint16_t x = l1[ind].x; x <= l2[ind].x; ++x)
        {
            result.push_back({ x, y });
        }
    }

    const point mid_point = result.back();

    l1 = make_line_int(p2, p3);
    l2 = make_line_int(mid_point, p3);

    // render_lines_list_test({{{p2, p3}}}, "l1_img.ppm", make_line_int);

    render_line_test(l1, "l1_line.ppm");


    for (uint16_t ind = 1; ind <= (p3.y - p2.y); ++ind)
    {
        const uint16_t y = p2.y + ind;

        for (uint16_t x = l1[ind].x; x <= l2[ind].x; ++x)
        {
            result.push_back({ x, y });
        }
    }

    return result;
}
