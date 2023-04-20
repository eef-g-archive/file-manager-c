#include "../headers/part.h"

Partition* Partition_new(FILE* file, int* offset, int type)
{
    Partition* self = (Partition*)malloc(sizeof(Partition));
    Partition_init(self, file, offset, type);
    return self;
}

void Partition_init(Partition* self, FILE* file, int* offset, int type)
{
    switch(type)
    {
        case 0:
        {
            self->fat16 = F16P_new(file, offset);
            break;
        }
        // case 1:
        //     self->fat32 = F32P_new(file, offset);
        //     break;
        default:
        {
            // This will be what happens when the partition type is not FAT 16
            // or FAT 32
            break;
        }
        
    }
    self->fat16 = F16P_new(file, offset);
}

void Partition_print(Partition* self)
{
    if(self->fat16 != NULL)
        F16P_print(self->fat16);
    else
        printf("No FAT16 partition found\n");
}

void Partition_destroy(Partition* self)
{
    F16P_destroy(self->fat16);
    free(self);
}