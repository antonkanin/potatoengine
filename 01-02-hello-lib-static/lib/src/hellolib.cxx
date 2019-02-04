#include "hellolib.h"
#include <iostream>

bool hello(const std::string& name)
{
    std::cout << "Hello " << name << "\n";
    return std::cout.good();
}