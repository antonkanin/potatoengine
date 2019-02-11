#pragma once

#include "image.h"
#include "point.h"

auto make_line_float(point p1, point p2)
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

            if (x == 0) // we have to this since we avoid 'overflow' for the unsigned int
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

auto make_line_int(point p1, point p2)
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

            if (2 * error > 1)
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

            if (x == 0) // we have to this since we avoid 'overflow' for the unsigned int
            {
                break;
            }

            --x;

            error += dy;

            if (2 * error > 1)
            {
                ++y;
                error -= dx;
            }
        }
    }

    return result;
}
