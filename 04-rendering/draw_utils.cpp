#include <cmath>

#include <cmath>

#include "draw_line_tests.h"
#include "draw_utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>

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

    if (p3.x >= p2.x)
    {
        ///////////////////////////////////////////////////////////////////
        // lower triangle

        float dxdy1 =
            static_cast<float>(p2.x - p1.x) / static_cast<float>(p2.y - p1.y);
        float dxdy2 =
            static_cast<float>(p3.x - p1.x) / static_cast<float>(p3.y - p1.y);

        std::cout << "p1 " << p1.x << ' ' << p1.y << '\n';

        auto y = p1.y;

        float c1 = dxdy1 * p1.y - p1.x;
        float c2 = dxdy2 * p1.y - p1.x;

        while (y <= p2.y)
        {
            auto x1 = static_cast<uint16_t>(std::round(dxdy1 * y - c1));
            auto x2 = static_cast<uint16_t>(std::round(dxdy2 * y - c2));

            result.push_back({ x1, y });
            result.push_back({ x2, y });

            ++y;
        }

        ///////////////////////////////////////////////////////////////////
        // upper triangle

//        auto mid_x = result.back().x;
//
//        dxdy1 =
//            static_cast<float>(p3.x - p2.x) / static_cast<float>(p3.y - p2.y);
//
//        dxdy2 = static_cast<float>(p3.x - mid_x) / static_cast<float>(p3.y - y - 1);
//
//        c1 = dxdy1 * p2.y - p1.x;
//        c2 = dxdy2 * p2.y - mid_x;
//
//        while (y <= p3.y)
//        {
//            auto x1 = static_cast<uint16_t>(dxdy1 * y - c1);
//            auto x2 = static_cast<uint16_t>(dxdy2 * y - c2);
//
//            std::cout << x1 << ' ' << x2 << '\n';
//
//            result.push_back({ x1, y });
//            result.push_back({ x2, y });
//
//            ++y;
//        }
    }

    return result;
}
