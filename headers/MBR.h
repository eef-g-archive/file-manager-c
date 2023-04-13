#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MBR {
    unsigned char bootCode[446];
    struct PartitionEntry {
        unsigned char status;
        unsigned char CHSFirstSector[3];
        unsigned char type;
        unsigned char CHSLastSector[3];
        unsigned int LBAFirstSector;
        unsigned int sectorsCount;
    } partitionEntry[4];
    unsigned short signature;
} MBR;

typedef struct PartitionEntry PartitionEntry;


MBR* MBR_new(FILE* file); // Won't need to worry about a constructor param since this will be passed in from cmd args
void MBR_init(MBR* self, FILE* file);
void MBR_destroy(MBR* self);
void MBR_print(MBR* self);
void _readPartition(PartitionEntry* partition, FILE* file);