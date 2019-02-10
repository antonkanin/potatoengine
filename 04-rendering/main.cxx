#include "image.h"
#include "point.h"
#include <array>
#include <memory>
#include <stdlib.h>

auto make_line(point p1, point p2)
{
    std::vector<point> result;

    if (p2.y < p1.y)
    {
        swap(p1, p2);
    }

    const auto dy = abs(p2.y - p1.y);
    const auto dx = abs(p2.x - p1.x);

    if (p1.x <= p2.x)
    {
        auto x = p1.x;
        auto y = p1.y;

        while (x <= p2.x)
        {
            result.push_back({ x, y });

            if (2 * (dy * x - dx * y) > dx)
            {
                ++y;
            }

            ++x;
        }
    }
    else
    {
        auto x = p2.x;
        auto y = p2.y;

        // this crap ain't workin correctly...
        while (x <= p1.x)
        {
            result.push_back({ x, y });

            if (2 * (dy * x - dx * y) > dx)
            {
                --y;
            }

            ++x;
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

    //    img->draw_line(make_line({ 0, 0 }, { 9, 9 }), blue);
    //    img->draw_line(make_line({ 0, 0 }, { 9, 4 }), blue);
    //
    //    img->draw_line(make_line({ 9, 0 }, { 0, 9 }), red);
    img->draw_line(make_line({ 9, 0 }, { 0, 4 }), red);

    img->save("img_01.ppm");

    return EXIT_SUCCESS;
}