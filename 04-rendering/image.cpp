#include "image.h"

image::image(const uint16_t width, const uint16_t height)
    : width_(width)
    , height_(height)
{
}

color& image::pixel(const uint16_t x, const uint16_t y)
{
    return pixels_[y * width_ + x];
}

bool image::save(const std::string &file_name)
{
    std::ofstream out_file(file_name, std::ios::binary);

    if (out_file.is_open() == false)
    {
        return false;
    }

    out_file << "P6\n" << width_ << ' ' << height_ << 255 << '\n';
    out_file.write(reinterpret_cast<char*>(pixels_.data()), pixels_.size());

    return true;
}