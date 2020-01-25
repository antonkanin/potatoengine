#pragma once

#include <engine.hpp>
#include <string_view>

namespace pt
{

void load_scene(engine& engine, std::string_view file_path);

void save_scene(engine& engine, std::string_view file_path);

} // namespace pt