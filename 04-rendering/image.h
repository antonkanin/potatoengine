#pragma once

#include "color.h"
#include <array>
#include <fstream>
#include <string>
#include <vector>

class image
{
public:
    image() = delete;

    image(const uint16_t width, const uint16_t height)
        : width_(width)
        , height_(height)
    {
    }

    bool load(const std::string& filename)
    {
        std::ifstream in_file(filename, std::ios::binary);

        if (in_file.is_open() == false)
        {
            return false;
        }
    }

    bool save(const std::string& filename) { std::ofstream out_file(filename); }

private:
    uint16_t width_;
    uint16_t height_;

    std::vector<color> pixels_;
};
