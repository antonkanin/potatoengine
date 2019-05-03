#pragma once

#include <string>
#include <memory>

namespace pt
{

std::unique_ptr<class model> load_model_from_file(const std::string& path);

}