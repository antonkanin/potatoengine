#include <iostream>
#include <string>

#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT
#endif

extern "C" EXPORT bool hello(const std::string& name)
{
    std::cout << "Hello " << name << "\n";
    return std::cout.good();
}