#include "texture_image.hpp"
#include "../ext/picopng.hpp"

namespace pt
{

void texture_image::load(const std::string& file_name)
{
    std::vector<unsigned char> buffer;
    loadFile(buffer, file_name);

    int error =
        decodePNG(image_data_, width_, height_, buffer.empty() ? 0 : &buffer[0],
                  buffer.size(), false);

    // if there's an error, display it
    if (error != 0)
    {
        throw std::runtime_error("Error: failed to load png file: " + file_name);
    }
}

size_t texture_image::width() const
{
    return width_;
}

size_t texture_image::height() const
{
    return height_;
}

const unsigned char* texture_image::get_data() const
{
    return image_data_.data();
}

texture_image make_image(const std::string& file_name)
{
    texture_image result;
    result.load(file_name);
    return result;
}

} // namespace pt