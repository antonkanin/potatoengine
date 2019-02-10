#pragma once

#include <cstdint>

struct point
{
    uint16_t x;
    uint16_t y;
};

void swap(point &p1, point &p2);
