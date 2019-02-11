#include "image.h"
#include "point.h"
#include <array>
#include <memory>
#include <stdlib.h>

auto make_line(point p1, point p2)
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

    const float dydx =
        abs(static_cast<float>(p2.y - p1.y) / static_cast<float>(p2.x - p1.x));

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

            if (x == 0)
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

int main(int argc, char* argv[])
{
    const u_int8_t WIDTH  = 10;
    const u_int8_t HEIGHT = 10;

    auto img = std::make_unique<image>(WIDTH, HEIGHT);

    img->fill(green);

    img->draw_line(make_line({ 0, 0 }, { 9, 9 }), blue);
    img->draw_line(make_line({ 0, 0 }, { 9, 4 }), blue);
    img->draw_line(make_line({ 0, 0 }, { 4, 9 }), blue);

    img->save("img_01.ppm");

    // second image

    auto img2 = std::make_unique<image>(WIDTH, HEIGHT);

    img2->fill(green);

    img2->draw_line(make_line({ 0, 9 }, { 9, 0 }), blue);
    img2->draw_line(make_line({ 0, 9 }, { 9, 4 }), blue);
    img2->draw_line(make_line({ 0, 9 }, { 4, 0 }), blue);

    img2->save("img_02.ppm");

    return EXIT_SUCCESS;
}