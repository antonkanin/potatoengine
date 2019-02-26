#include "texture_image.hpp"

namespace pt
{

void texture_image::load(const std::string& file_name)
{
    // load the image data...
}

size_t texture_image::width() const
{
    return width_;
}

size_t texture_image::height() const
{
    return height_;
}

texture_image::~texture_image()
{
    if (image_data_ != nullptr)
    {
        delete[] image_data_;
        image_data_ = nullptr;
    }
}

unsigned char* texture_image::get_data() const
{
    return image_data_;
}

texture_image* make_image(const std::string& file_name)
{
    auto* result = new texture_image();
    result->load(file_name);
    return result;
}

} // namespace pt