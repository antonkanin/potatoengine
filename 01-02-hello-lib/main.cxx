#include <windows.h>
#include <iostream>
#include <string>

typedef bool (*f_hello)(const std::string&);

int main(int argc, char* argv[])
{
    HINSTANCE helloDll = LoadLibrary("hellolib.dll");
    if (helloDll == nullptr)
    {
        std::cout << "Cannot locate hellolib.dll" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        f_hello hello = (f_hello)GetProcAddress(helloDll, "hello");
        if (!hello)
        {
            if (hello("Anton"))
            {
                return EXIT_SUCCESS;
            }
        }
        else
        {
            // TODO add error handling if we did not find a function in the dll
        }
    }

    return EXIT_FAILURE;
}