#include <iostream>
#include "hellolib.h"

bool hello(const std::string& name)
{
    std::cout << "Hello " << name << "\n";
    return std::cout.good();
}