#include "reader.h"
#include "commands.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <disk image>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to a char* -- This way we can actually parse the file!
    char* file = argv[1];

    InitializeFileManager(file);
    MainLoop();

    return 0;   
}
