#include "../headers/Partition.h"

#pragma region ReservedSectors Functions

ReservedSectors* ReservedSectors_new(FILE* file, int offset)
{
    ReservedSectors* self = (ReservedSectors*) malloc(sizeof(ReservedSectors));
    ReservedSectors_init(self, file, offset);
    return self;
}

void ReservedSectors_init(ReservedSectors* self, FILE* file, int offset)
{
    self->boot = BootSector_new(file, offset);
    //self->fsInfo = FSInfo_new(file);
}

void ReservedSectors_print(ReservedSectors* self)
{
    BootSector_print(self->boot);
    //FS_print(self->fsInfo);
}

void ReservedSectors_destroy(ReservedSectors* self)
{
    BootSector_destroy(self->boot);
    FSInfo_destroy(self->fsInfo);
    free(self);
}

BootSector* BootSector_new(FILE* file, int offset)
{
    BootSector* self = (BootSector*) malloc(sizeof(BootSector));
    BootSector_init(self, file, offset);
    return self;
}

void BootSector_init(BootSector* self, FILE* file, int offset)
{
    fread(&self->bytesPerSector, 2, 1, file);
    fread(&self->sectorsPerCluster, 1, 1, file);
    fread(&self->reservedSectors, 2, 1, file);
    fread(&self->fatCopies, 1, 1, file);
    fread(&self->rootEntries, 2, 1, file);
    fread(&self->totalSectors, 2, 1, file);
    fread(&self->mediaDescriptor, 1, 1, file);
    fread(&self->sectorsPerFAT, 2, 1, file);
    fread(&self->sectorsPerHead, 2, 1, file);
    fread(&self->headsPerCylinder, 2, 1, file);
    fread(&self->hiddenSectors, 4, 1, file);
    fread(&self->bigNumberofSectors, 4, 1, file);
    fread(&self->bigNumberSectorsPerFAT32, 4, 1, file);
    fread(&self->flags, 2, 1, file);
    fread(&self->version, 2, 1, file);
    fread(&self->rootCluster, 4, 1, file);
    fread(&self->fsInfoSector, 2, 1, file);
    fread(&self->backupBootSector, 2, 1, file);
    fread(&self->reserved, 12, 1, file);
}

void BootSector_print(BootSector* self)
{
    printf("Bytes per sector: %X\n", self->bytesPerSector);
    printf("Sectors per cluster: %X\n", self->sectorsPerCluster);
    printf("Reserved sectors: %X\n", self->reservedSectors);
    printf("FAT copies: %X\n", self->fatCopies);
    printf("Root entries: %X\n", self->rootEntries);
    printf("Total sectors: %X\n", self->totalSectors);
    printf("Media descriptor: %X\n", self->mediaDescriptor);
    printf("Sectors per FAT: %X\n", self->sectorsPerFAT);
    printf("Sectors per head: %X\n", self->sectorsPerHead);
    printf("Heads per cylinder: %X\n", self->headsPerCylinder);
    printf("Hidden sectors: %X\n", self->hiddenSectors);
    printf("Big number of sectors: %X\n", self->bigNumberofSectors);
    printf("Big number of sectors per FAT32: %X\n", self->bigNumberSectorsPerFAT32);
    printf("Flags: %X\n", self->flags);
    printf("Version: %X\n", self->version);
    printf("Root cluster: %X\n", self->rootCluster);
    printf("FS Info sector: %X\n", self->fsInfoSector);
    printf("Backup boot sector: %X\n", self->backupBootSector);
}

void BootSector_destroy(BootSector* self)
{
    free(self);
}

FSInfo* FSInfo_new(FILE* file, int offset)
{
    FSInfo* self = (FSInfo*) malloc(sizeof(FSInfo));
    FSInfo_init(self, file, offset);
    return self;
}

void FSInfo_init(FSInfo* self, FILE* file, int offset)
{
    fread(&self->signature, 4, 1, file);
    fread(&self->reserved, 480, 1, file);
    fread(&self->signature2, 4, 1, file);
    fread(&self->freeClusterCount, 4, 1, file);
    fread(&self->nextFreeCluster, 4, 1, file);
    fread(&self->reserved2, 12, 1, file);
    fread(&self->signature3, 4, 1, file);
}

void FS_print(FSInfo* self)
{
    printf("Signature: %d", self->signature);
    printf("Signature2: %d", self->signature2);
    printf("Free cluster count: %d", self->freeClusterCount);
    printf("Next free cluster: %d", self->nextFreeCluster);
    printf("Signature3: %d", self->signature3);
}

void FSInfo_destroy(FSInfo* self)
{
    free(self);
}



#pragma endregion



Partition* Partition_new(FILE* file, int offset)
{
    Partition* self = (Partition*) malloc(sizeof(Partition));
    Partition_init(self, file, offset);
    return self;
}

void Partition_init(Partition* self, FILE* file, int offset)
{
    self->reserved = ReservedSectors_new(file, offset);
}

void Partition_print(Partition* self)
{
    printf("\n\n-=| Partition |=-\n");
    ReservedSectors_print(self->reserved);
}
