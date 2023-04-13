#include "headers/MBR.h"

int main(int argc, char* argv[])
{
    printf("Usage: %s <img file>\n", argv[0]);
    if(argc < 2)
    {
        printf("No img file specified\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "rb");
    MBR* mbr = MBR_new(file);
    MBR_print(mbr);
    MBR_destroy(mbr);
    return 0;   
}