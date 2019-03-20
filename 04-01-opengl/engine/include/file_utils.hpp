#pragma once

#include <engine.hpp>
#include <string_view>

namespace pt
{

void load_scene(const engine& engine, std::string_view file_path);

}