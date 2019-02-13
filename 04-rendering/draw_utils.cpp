#include <cmath>

#include <cmath>

#include "draw_line_tests.hpp"
#include "draw_utils.hpp"
#include "point.hpp"
#include "point_array.hpp"
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

        int error = 0;

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

        int error = 0;

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

    // TRUE if P1 -> P2 -> P3 make a clockwise direction
    bool is_clockwise = (p1.y == p2.y && p2.x < p1.x);
    is_clockwise      = is_clockwise || (p2.y == p3.y && p2.x <= p3.x);
    is_clockwise      = is_clockwise || (p3.x <= p2.x && p2.x <= p1.x);
    is_clockwise      = is_clockwise || (p2.x <= p1.x && p1.x <= p3.x);
    is_clockwise      = is_clockwise || (p1.x <= p2.x && p2.x <= p3.x);

    uint16_t mid_x = 0;

    ///////////////////////////////////////////////////////////////////
    // lower triangle
    if (p2.y != p1.y)
    {
        float dxdy1 =
            static_cast<float>(p2.x - p1.x) / static_cast<float>(p2.y - p1.y);
        float dxdy2 =
            static_cast<float>(p3.x - p1.x) / static_cast<float>(p3.y - p1.y);

        auto y = p1.y;

        float c1 = dxdy1 * p1.y - p1.x;
        float c2 = dxdy2 * p1.y - p1.x;

        while (y <= p2.y)
        {
            auto x1 = static_cast<uint16_t>(std::round(dxdy1 * y - c1));
            auto x2 = static_cast<uint16_t>(std::round(dxdy2 * y - c2));

            if (is_clockwise)
            {
                for (auto ind = x1; ind <= x2; ++ind)
                {
                    result.push_back({ ind, y });
                }
            }
            else
            {
                for (auto ind = x2; ind <= x1; ++ind)
                {
                    result.push_back({ ind, y });
                }
            }

            mid_x = x2;

            ++y;
        }
    }
    else
    {
        if (is_clockwise)
        {
            for (auto ind = p2.x; ind <= p1.x; ++ind)
            {
                result.push_back({ ind, p1.y });
            }

            mid_x = p1.x;
        }
        else
        {
            for (auto ind = p1.x; ind <= p2.x; ++ind)
            {
                result.push_back({ ind, p1.y });
            }

            mid_x = p2.x;
        }
    }

    /////////////////////////////////////////////////////////////////////
    // upper triangle
    if (p3.y != p2.y)
    {
        float dxdy1 =
            static_cast<float>(p3.x - p2.x) / static_cast<float>(p3.y - p2.y);

        float dxdy2 =
            static_cast<float>(p3.x - p1.x) / static_cast<float>(p3.y - p1.y);

        auto c1 = dxdy1 * p2.y - p2.x;
        auto c2 = dxdy2 * p2.y - mid_x;

        auto y = static_cast<uint16_t>(p2.y + 1);

        while (y <= p3.y)
        {
            auto x1 =
                static_cast<uint16_t>(std::abs(std::round(dxdy1 * y - c1)));
            auto x2 =
                static_cast<uint16_t>(std::abs(std::round(dxdy2 * y - c2)));

            if (is_clockwise)
            {
                for (auto ind = x1; ind <= x2; ++ind)
                {
                    result.push_back({ ind, y });
                }
            }
            else
            {
                for (auto ind = x2; ind <= x1; ++ind)
                {
                    result.push_back({ ind, y });
                }
            }

            ++y;
        }
    }

    return result;
}

std::vector<point> make_triangle(const std::vector<point>& points)
{
    // I deliberately do not check of any exceptions as I want to crash when
    // something goes wrong
    return make_triangle(points[0], points[1], points[2]);
}
