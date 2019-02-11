#include "draw_utils.h"
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

    if (p2.y < p1.y)
    {
        swap(p1, p2);
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

    if (p2.y < p1.y)
    {
        swap(p1, p2);
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

    return result;
}

std::vector<point> make_triangle(point p1, point p2, point p3)
{
    std::vector<point> result;

    std::vector<point> tr = { p1, p2, p3 };
    std::sort(begin(tr), end(tr),
              [](const point& p1_, const point& p2_) { return p1_.y < p2_.y; });

    auto l1 = make_line_int(p1, p2);
    auto l2 = make_line_int(p1, p3);

    for (uint16_t ind = 0; ind < (p2.y - p1.y); ++ind)
    {
        for (uint16_t x = l1[ind].x; x <= l2[ind].x; ++x)
        {
            uint16_t y = l2[ind].y + ind;
            result.push_back({x, y});
        }
    }

    return result;
}
