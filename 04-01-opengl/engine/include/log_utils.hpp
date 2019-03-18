#pragma once

#include <iostream>

namespace pt
{

inline void log_line(const std::string& line)
{
    std::cout << line << '\n';
}

inline void log_line(const float time, const std::string& line)
{
    std::cout << time <<  " " << line << std::endl;
}

} // namespace pt