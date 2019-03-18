#pragma once

#include <iostream>

namespace pt
{

inline void log_line(const std::string& line)
{
    std::cout << line << '\n';
}

} // namespace pt