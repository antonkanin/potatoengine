#pragma once

#include "draw_utils.h"

void draw_line_tests()
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

    // third image

    auto img3 = std::make_unique<image>(WIDTH, HEIGHT);

    img3->fill(green);

    img3->draw_line(make_line({ 9, 0 }, { 0, 9 }), blue);
    img3->draw_line(make_line({ 9, 0 }, { 0, 4 }), blue);
    img3->draw_line(make_line({ 9, 0 }, { 4, 9 }), blue);

    img3->save("img_03.ppm");

    // forth image

    auto img4 = std::make_unique<image>(WIDTH, HEIGHT);

    img4->fill(green);

    img4->draw_line(make_line({ 9, 9 }, { 0, 0 }), blue);
    img4->draw_line(make_line({ 9, 9 }, { 0, 4 }), blue);
    img4->draw_line(make_line({ 9, 9 }, { 4, 0 }), blue);

    img4->save("img_04.ppm");
}
