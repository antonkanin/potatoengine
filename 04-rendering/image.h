#pragma once

#include "color.h"
#include <array>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class image
{
public:
    image() = delete;

    image(const uint16_t width, const uint16_t height);

    bool save(const std::string &file_name);

    color& pixel(const uint16_t x, const uint16_t y);

private:
    uint16_t width_;
    uint16_t height_;

    std::vector<color> pixels_;
};
