#pragma once

#include <stdint-gcc.h>

struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

const color white = { 255, 255, 255 };
const color black = { 0, 0, 0 };
const color red   = { 255, 0, 0 };
const color green = { 0, 255, 0 };
const color blue  = { 0, 0, 255 };