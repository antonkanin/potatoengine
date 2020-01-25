#include <chrono>
#include <ctime>
#include <iostream>
#include <log_utils.hpp>

namespace pt
{

auto current_time()
{
    auto timenow =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    return ctime(&timenow);
}

void log_line(const float time, const std::string& line)
{
    std::cout << time << " " << line << std::endl;
}

void log_line(const std::string& line)
{
    // std::cout << current_time() << ' ' << line << '\n';
    std::cout << line << std::endl;
}

std::ostream& log_line()
{
    // std::cout << current_time() << ": ";
    return std::cout;
}

void log_error(const std::string& line)
{
    std::cerr << line << std::endl;
}

void log_error(float time, const std::string& line)
{
    std::cerr << time << " " << line << std::endl;
}

} // namespace pt