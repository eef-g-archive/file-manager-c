#include "headers/reader.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Usage: %s <disk image>\n", argv[0]);
        return 1;
    }

    // Convert argv[1] to a char* -- This way we can actually parse the file!
    char* file = argv[1];
    ReadDiskImage(file);
    printf("%s is a valid disk image!\n", file);

    return 0;   
}
