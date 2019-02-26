#pragma once

#include <cstdlib>
#include <string>
#include <vector>

namespace pt
{

class texture_image
{
public:
    void load(const std::string& file_name);

    size_t width() const;
    size_t height() const;

    const unsigned char* get_data() const;

private:
    size_t width_  = 0;
    size_t height_ = 0;

    std::vector<unsigned char> image_data_;
};

texture_image make_image(const std::string& file_name);

} // namespace pt