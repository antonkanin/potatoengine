#pragma once

#include <iostream>
#include <string>

bool hello(const std::string& name)
{
    std::cout << "Hello " << name << "\n";
    return std::cout.good();
}