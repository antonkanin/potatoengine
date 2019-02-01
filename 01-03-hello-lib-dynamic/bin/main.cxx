#ifdef _WIN32
    #include <windows.h> // we need this for LoadLibrary and GetProcAddress in Windows
#else
    #include <dlfcn.h>  // and this one is for dlopen and dlsym in Linux
#endif

#include <iostream>
#include <string>

typedef bool (*f_hello)(const std::string&);

int main(int argc, char* argv[])
{
    using namespace std;
    
#ifdef _WIN32
    HINSTANCE helloDll = LoadLibrary("hello.dll");
#else
    void* helloDll = dlopen("libhello.so", RTLD_LAZY);
#endif

    if (helloDll == nullptr)
    {
        cout << "Could not load hello library" << endl;
    }
    else
    {
#ifdef _WIN32
        f_hello hello = (f_hello)GetProcAddress(helloDll, "hello");
#else
        f_hello hello = (f_hello)dlsym(helloDll, "hello");
#endif

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
            cout << "Could not find hello function in the hello library" << endl;
        }
    }

    return EXIT_FAILURE;
}