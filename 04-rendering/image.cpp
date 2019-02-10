#include "image.h"
#include "point.h"

image::image(const uint16_t width, const uint16_t height)
    : width_(width)
    , height_(height)
{
    pixels_.resize(width * height);
}

const color image::get_color(const point& point_val) const
{
    return pixels_[point_val.x + point_val.y * width_];
}

void image::set_color(const point& point_val, const color& color_val)
{
    pixels_[point_val.x + point_val.y * width_] = color_val;
}

uint16_t image::width() const
{
    return width_;
}

uint16_t image::height() const
{
    return height_;
}

bool image::save(const std::string& file_name)
{
    std::ofstream out_file(file_name, std::ios::binary);

    if (out_file.is_open() == false)
    {
        return false;
    }

    out_file << "P6\n" << width_ << ' ' << height_ << ' ' << 255 << '\n';
    out_file.write(reinterpret_cast<char*>(pixels_.data()),
                   sizeof(color) * pixels_.size());

    return true;
}

const image& image::fill(const color& color)
{
    std::fill(begin(pixels_), end(pixels_), color);

    return *this;
}

const image& image::draw_line(const std::vector<point>& points,
                        const color&              color_val)
{
    for (const auto& p : points)
    {
        this->set_color(p, color_val);
    }

    return *this;
}
