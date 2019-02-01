#include <windows.h>
#include <iostream>
#include <string>

typedef bool (*f_hello)(const std::string&);

int main(int argc, char* argv[])
{
    using namespace std;
    
    HINSTANCE helloDll = LoadLibrary("hellolib.dll");
    if (helloDll == nullptr)
    {
        cout << "Could not load hellolib.dll" << endl;
    }
    else
    {
        f_hello hello = (f_hello)GetProcAddress(helloDll, "hello");
        if (hello)
        {
            if (hello("Anton"))
            {
                return EXIT_SUCCESS;
            }
            
            cout << "There was an error in the hello function" << endl;
        }
        else
        {
            cout << "Could not find hello function in the hellolib.dll" << endl;
        }
    }

    return EXIT_FAILURE;
}