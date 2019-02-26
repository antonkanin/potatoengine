#pragma once

#include <cstdlib>
#include <string>

namespace pt
{

class texture_image
{
public:
    void load(const std::string& file_name);

    size_t width() const;
    size_t height() const;

    unsigned char* get_data() const;

    ~texture_image();

private:
    size_t width_  = 0;
    size_t height_ = 0;

    unsigned char* image_data_ = nullptr;
};

texture_image* make_image(const std::string& file_name);

} // namespace pt