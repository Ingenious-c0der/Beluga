#include "core.cpp"
#include "file_handler.h"

int main(int argc, char *argv[])
{
    //handle file related errors
    if (argc == 1)
    {
        std::cout << "No Beluga file path specified" << std::endl;
        return 0;
    }
    if (argc == 2)
    {
        //handle file related errors
        sanitize_file(argv[1]);
        execute(argv[1]);
    }
    return 0;
}