#include "hellolib.h"

int main(int argc, char* argv[])
{
    if (hello("Anton"))
    {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}