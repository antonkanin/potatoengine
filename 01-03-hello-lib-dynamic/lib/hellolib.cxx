#include <iostream>
#include <string>

extern "C" __declspec(dllexport) bool hello(const std::string& name)
{
    std::cout << "Hello " << name << "\n";
    return std::cout.good();
}