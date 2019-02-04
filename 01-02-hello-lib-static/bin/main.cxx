#include <hellolib.h>
#include <string>

int main(int argc, char* argv[])
{
    using namespace std;

    if (hello("Anton"))
    {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}