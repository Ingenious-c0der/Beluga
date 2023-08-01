#include "core.cpp"
#include "file_handler.h"
#include<vector>





int main(int argc, char *argv[])
{
    std::vector<Flag> flags; 
    
    if (argc == 1)
    {
        std::cout << "No Beluga file path specified" << std::endl;
        return 0;
    }
    if (argc == 2) //remove this later
    {
        //handle file related errors
        sanitize_file(argv[1]);
        execute(argv[1],flags);
    }
    if(argc > 2)
    {
        for(int i = 2; i < argc; i++)
        {
           if (strcmp(argv[i], "-t") == 0)
           {
                flags.push_back(Flag(TIME_DEBUG, true));
           }
        }
        sanitize_file(argv[1]);
        execute(argv[1],flags);
        return 0;
    }
    return 0;
}