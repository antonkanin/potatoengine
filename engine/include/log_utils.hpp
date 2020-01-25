#pragma once

#include <iostream>

namespace pt
{

std::ostream& log_line();

void log_line(const std::string& line);

void log_line(float time, const std::string& line);

void log_error(const std::string& line);

void log_error(float time, const std::string& line);

} // namespace pt