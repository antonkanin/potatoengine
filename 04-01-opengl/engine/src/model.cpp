#include "model.hpp"
#include <cstdlib>
#include <model.hpp>


namespace pt
{

model::~model()
{
    if (image != nullptr)
    {
        delete[] image;
        image = nullptr;
    }
}

} // namespace pt