#pragma once

#include <string>

namespace pt
{
void log_line(const std::string& line);

void log_line(float time, const std::string& line);

void log_error(const std::string& line);

void log_error(float time, const std::string& line);
} // namespace pt