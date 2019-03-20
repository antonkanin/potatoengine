#include <chrono>
#include <ctime>
#include <iostream>
#include <log_utils.hpp>

auto current_time()
{
    auto timenow =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    return ctime(&timenow);
}

void pt::log_line(const float time, const std::string& line)
{
    std::cout << time << " " << line << std::endl;
}

void pt::log_line(const std::string& line)
{
    std::cout << current_time() << ' ' << line << '\n';
}

std::ostream& pt::log_line()
{
    //std::cout << current_time() << ": ";
    return std::cout;
}
