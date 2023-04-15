#include "headers/reader.h"

int main(int argc, char* argv[])
{
    printf("This is a test");
    printf("Usage: %s <img file>\n", argv[0]);
    if(argc < 2)
    {
        printf("No img file specified\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "rb");
    Reader* reader = Reader_new(file);
    Reader_print(reader);
    return 0;   
}
