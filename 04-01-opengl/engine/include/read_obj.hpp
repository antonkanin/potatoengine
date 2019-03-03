#pragma once

#include "mesh.hpp"
#include <string>

namespace pt
{

mesh read_obj(const std::string& file_name);

}