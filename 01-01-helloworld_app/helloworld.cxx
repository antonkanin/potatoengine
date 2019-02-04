#include <iostream>

int main(int agrc, char* argv[])
{
    std::cout << "Hello world" << std::endl;
    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}
