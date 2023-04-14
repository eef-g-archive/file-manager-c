#include <stdlib.h>
#include <stdio.h>


typedef struct PartitionEntry
{
    __uint8_t status;
    __uint8_t CHSFirstSector[3];
    __uint8_t type;
    __uint8_t CHSLastSector[3];
    __uint64_t LBAFirstSector;
    __uint64_t sectorsCount
} __attribute__ ((packed)) PartitionEntry;

typedef struct MBR {
    __uint8_t bootCode[446];
    PartitionEntry partitionEntry[4];
    __uint16_t signature;
} MBR;


MBR* MBR_new(FILE* file); // Won't need to worry about a constructor param since this will be passed in from cmd args
void MBR_init(MBR* self, FILE* file);
void MBR_destroy(MBR* self);
void MBR_print(MBR* self);


void _readPartition(PartitionEntry* partition, FILE* file);
void _printStatus(PartitionEntry entry);
void _printType(PartitionEntry entry);