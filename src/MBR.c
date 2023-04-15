#include "../headers/MBR.h"
#include "../headers/utility.h"

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
}

void MBR_destroy(MBR* self) {
   free(self);
}


void MBR_print(MBR* self)
{
    // printf("Boot Code: ");
    // for (int i = 0; i < 446; i++) {
    //     printf("%02x ", self->bootCode[i]);
    // }
    for (int i = 0; i < 4; i++) {
        printf("Partition %d:\n", i + 1);
        _printStatus(self->partitionEntry[i]);
        printf("\tCHS First Sector: 0x%X%X%X\n", self->partitionEntry[i].CHSFirstSector[0], self->partitionEntry[i].CHSFirstSector[1], self->partitionEntry[i].CHSFirstSector[2]);
        _printType(self->partitionEntry[i]);
        printf("\tCHS Last Sector: 0x%X%X%X\n", self->partitionEntry[i].CHSLastSector[0], self->partitionEntry[i].CHSLastSector[1], self->partitionEntry[i].CHSLastSector[2]);
        printf("\tLBA First Sector: 0x%04X\n", self->partitionEntry[i].LBAFirstSector);
        printf("\tSectors Count: 0x%04X\n", self->partitionEntry[i].sectorsCount);
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

void _printStatus(PartitionEntry entry)
{
    printf("\tStatus: ");

    #pragma region Status
    switch(entry.status)
    {
        case 0x00:
        {
            printf("Inactive");
            break;
        }
        case 0x80:
        {
            printf("Active");
            break;
        }
        default:
        {
            printf("Unknown");
            break;
        }
    }
    #pragma endregion
    
    printf("\n");
}

void _printType(PartitionEntry entry)
{
    printf("\tType: ");

    #pragma region TypeCodes
    
    switch(entry.type)
    {
        case 0x00:
        {
            printf("Empty");
            break;
        }
        case 0x01:
        {
            printf("FAT12");
            break;
        }
        case 0x04:
        {
            printf("FAT16");
            break;
        }
        case 0x06:
        {
            printf("FAT16");
            break;
        }
        case 0x0b:
        {
            printf("FAT32");
            break;
        }
        case 0x0e:
        {
            printf("FAT16 LBA");
            break;
        }
        case 0x0c:
        {
            printf("FAT32 LBA");
            break;
        }
        case 0x07:
        {
            printf("NTFS");
            break;
        }
        case 0x83:
        {
            printf("Linux");
            break;
        }
        default:
        {
            printf("Unknown");
            break;
        }
    }

    #pragma endregion
    
    printf("\n");
}

