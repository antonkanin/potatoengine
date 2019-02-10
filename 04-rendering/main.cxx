#include "image.h"
#include "point.h"
#include <array>
#include <memory>
#include <stdlib.h>

auto make_line(point p1, point p2)
{
    std::vector<point> result;

    if ((p2.x < p1.x && p2.y < p1.y) || (p1.x < p2.x && p2.y < p1.y))
    {
        swap(p1, p2);
    }

    if (p2.x >= p1.x)
    {
        auto y = p1.y;

        // const float dydx = (static_cast<float>(p2.y - p1.y)) / (p2.x - p1.x);
        const auto dy = abs(p2.y - p1.y);
        const auto dx = abs(p2.x - p1.x);

        for (auto x = p1.x; x <= p2.x; ++x)
        {
            if (2 * (dy * x - y * dx) > dx)
            {
                ++y;
            }

            result.push_back({ x, y });
        }
    }
    else
    {
        auto y = p2.y;

        const auto dy = abs(p2.y - p1.y);
        const auto dx = abs(p2.x - p1.x);

        for (auto x = p2.x; x <= p1.x; ++x)
        {
            result.push_back({ x, y });

            if (2 * abs(dy * x + y * dx) > dx)
            {
                --y;
            }
        }
    }

    return result;
}

int main(int argc, char* argv[])
{
    u_int8_t const WIDTH  = 5;
    u_int8_t const HEIGHT = 5;

    auto img = std::make_unique<image>(WIDTH, HEIGHT);

    img->fill(green);

    //img->draw_line(make_line({ 0, 0 }, { 9, 9 }), blue);
    img->draw_line(make_line({ 2, 0 }, { 0, 2 }), red);

    img->save("img_01.ppm");

    return EXIT_SUCCESS;
}