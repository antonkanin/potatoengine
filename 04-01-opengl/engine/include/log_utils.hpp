#pragma once

#include <iostream>

namespace pt
{

std::ostream& log_line();

void log_line(const std::string& line);

void log_line(const float time, const std::string& line);

inline void log_error(const float time, const std::string line)
{
    std::cerr << time << "Error: " << line << std::endl;
}

} // namespace pt