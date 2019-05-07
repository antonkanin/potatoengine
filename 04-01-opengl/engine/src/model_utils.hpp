#pragma once

#include <string>
#include <memory>

namespace pt
{

std::unique_ptr<class model> load_model_from_file(const std::string& path);

void draw_model(std::unique_ptr<model>& model_ptr, class program& program);
void draw_model(const class model& model, class program& program);

}