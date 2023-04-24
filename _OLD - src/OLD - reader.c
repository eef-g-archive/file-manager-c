/*#include "../headers/reader.h"

Reader* Reader_new(FILE* filename)
{
    Reader* self = (Reader*) malloc(sizeof(Reader));
    Reader_init(self, filename);
    return self;
}

void Reader_init(Reader* self, FILE* filename)
{
    self->file = filename;
    self->mbr = MBR_new(filename);
    for (int i = 0; i < 4; i++) {
        self->offset = self->mbr->partitionEntry[i].LBAFirstSector * 512;
        // Check for file partition type. If it's 0x0c, it's a FAT32 partition
        // In the new function, passing in 0 as the type makes it a FAT16 partition
        if(self->mbr->partitionEntry[i].type == 0x0c)
            self->partitions[i] = Partition_new(filename, self->offset, 1);
        else
            self->partitions[i] = Partition_new(filename, self->offset, 0);
    }
}

void Reader_print(Reader* self)
{
    MBR_print(self->mbr);
    for (int i = 0; i < 4; i++) {
        printf("\n\n\t-=| Partition %d |=-\n", i + 1);
        if(self->mbr->partitionEntry[i].type == 0x00)
            printf("Inactive partition\n");
        else
            Partition_print(self->partitions[i]);
    }
}
*/