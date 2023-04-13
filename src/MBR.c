#include "../headers/MBR.h"
MBR* MBR_new(FILE* file) {
    MBR* self = (MBR*) malloc(sizeof(MBR));
    MBR_init(self, file);
    return self;
}

void MBR_init(MBR* self, FILE* file) {
    // Parse img file and fill MBR struct
    fread(&self->bootCode, 1, 446, file);
    for (int i = 0; i < 4; i++) {
        _readPartition(&self->partitionEntry[i], file);
    }
    fread(&self->signature, 2, 1, file);
    fclose(file);
}

void MBR_destroy(MBR* self) {
   free(self);
}


// TODO:
/*
    1. Change the "Type" to a switch case to print out the name of the drive type
    2. Change the "Status" to a switch case to print out the name of the status
    3. Change the LBA FIrst Sector & Sectors Count to print out in Hex & multiply by 512 to make it worth
*/

void MBR_print(MBR* self)
{
    printf("Boot Code: ");
    for (int i = 0; i < 446; i++) {
        printf("%02x ", self->bootCode[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("Partition %d:\n", i + 1);
        printf("\tStatus: %02x\n", self->partitionEntry[i].status);
        printf("\tCHS First Sector: %02x %02x %02x\n", self->partitionEntry[i].CHSFirstSector[0], self->partitionEntry[i].CHSFirstSector[1], self->partitionEntry[i].CHSFirstSector[2]);
        printf("\tType: %02x\n", self->partitionEntry[i].type);
        printf("\tCHS Last Sector: %02x %02x %02x\n", self->partitionEntry[i].CHSLastSector[0], self->partitionEntry[i].CHSLastSector[1], self->partitionEntry[i].CHSLastSector[2]);
        printf("\tLBA First Sector: %X\n", self->partitionEntry[i].LBAFirstSector * 512);
        printf("\tSectors Count: %X\n", self->partitionEntry[i].sectorsCount);
    }
    printf("Signature: %04x\n", self->signature);
}



void _readPartition(PartitionEntry* partition, FILE* file) {
    fread(&partition->status, 1, 1, file);
    fread(&partition->CHSFirstSector, 1, 3, file);
    fread(&partition->type, 1, 1, file);
    fread(&partition->CHSLastSector, 1, 3, file);
    fread(&partition->LBAFirstSector, 4, 1, file);
    fread(&partition->sectorsCount, 4, 1, file);
}