#pragma once

#include "color.h"
#include <array>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

struct point;

class image
{
public:
    image() = delete;

    image(const uint16_t width, const uint16_t height);


    // TODO come up with a better name for the method (perhaps 'get_color' ?)
    const color get_color(const point& point_val) const;
    void set_color(const point& point_val, const color& color_val);

    uint16_t width() const;
    uint16_t height() const;

    bool save(const std::string& file_name);

    image & fill(const color &color);

    const image& draw_line(const std::vector<point> &points, const color &color_val);


private:
    uint16_t width_;
    uint16_t height_;

    std::vector<color> pixels_;
};
