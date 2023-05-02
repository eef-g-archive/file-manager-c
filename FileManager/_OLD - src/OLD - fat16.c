/*
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../headers/fat16.h"

Fat16Partition* F16P_new(FILE* file, int* offset)
{
    Fat16Partition* self = (Fat16Partition*)malloc(sizeof(Fat16Partition));
    F16P_init(self, file, offset);
    return self;
}

void F16P_init(Fat16Partition* self, FILE* file, int* offset)
{
    self->bootSector = (BootSector*)malloc(sizeof(BootSector));
    self->allocationTables[0] = (AllocationTable*)malloc(sizeof(AllocationTable));
    self->allocationTables[1] = (AllocationTable*)malloc(sizeof(AllocationTable));
    self->directoryEntry = (DirectoryEntry*)malloc(sizeof(DirectoryEntry));
    _InitializeBootSector(self->bootSector, file, offset);
    _InitializeAllocationTable(self->allocationTables[0], file);
    _InitializeAllocationTable(self->allocationTables[1], file);
    _InitializeDirectoryEntry(self->directoryEntry, file);
}

void F16P_print(Fat16Partition* self)
{
    printf("\tFAT16 Partition:\n");
    printf("Boot Sector:\n");
    printf("\tJump: 0x%x%x%x\n", self->bootSector->jump[0], self->bootSector->jump[1], self->bootSector->jump[2]);
    printf("\tName: 0x%08x\n", self->bootSector->name);
    printf("\tBytes per sector: 0x%x\n", self->bootSector->bytesPerSector);
    printf("\tSectors per cluster: 0x%x\n", self->bootSector->sectorsPerCluster);
    printf("\tReserved sectors: 0x%x\n", self->bootSector->reservedSectors);
    printf("\tFAT copies: 0x%x\n", self->bootSector->fatCopies);
    printf("\tRoot entries: 0x%x\n", self->bootSector->rootEntries);
    printf("\tSmall number of sectors: 0x%x\n", self->bootSector->smallNumSectors);
    printf("\tMedia descriptor: 0x%x\n", self->bootSector->mediaDescriptor);
    printf("\tSectors per FAT: 0x%x\n", self->bootSector->sectorsPerFat);
    printf("\tSectors per track: 0x%x\n", self->bootSector->sectorsPerTrack);
    printf("\tNumber of heads: 0x%x\n", self->bootSector->numHeads);
    printf("\tHidden sectors: 0x%x\n", self->bootSector->hiddenSectors);
    printf("\tLarge number of sectors: 0x%x\n", self->bootSector->largeNumSectors);
    printf("\tDrive number: 0x%x\n", self->bootSector->driveNumber);
    printf("\tReserved: 0x%x\n", self->bootSector->reserved);
    printf("\tExtended boot signature: 0x%x\n", self->bootSector->extendedBootSignature);
    printf("\tVolume serial number: 0x%x\n", self->bootSector->volumeSerialNumber);
    printf("\tVolume label: 0x%x\n", self->bootSector->volumeLabel);
    printf("\tFile system type: 0x%x\n", self->bootSector->fileSystemType);

    printf("\nAllocation Table 1:\n");
    printf("Yeah I'm not printing that much data here :)\n");
    printf("\nAllocation Table 2:\n");
    printf("Yeah I'm not printing that much data here :)\n");
    
    printf("\nDirectory Entry:\n");
    printf("Name: %x\n", self->directoryEntry->name);
    printf("Extension: %x\n", self->directoryEntry->extension);
    printf("Attributes: %x\n", self->directoryEntry->attributes);
    printf("Reserved: %x\n", self->directoryEntry->reserved);
    printf("Creation time: %x\n", self->directoryEntry->creationTime);
    printf("Creation date: %x\n", self->directoryEntry->creationDate);
    printf("Last access date: %x\n", self->directoryEntry->lastAccessDate);
    printf("Last write time: %x\n", self->directoryEntry->lastWriteTime);
    printf("Last write date: %x\n", self->directoryEntry->lastWriteDate);
    printf("File size: %x\n", self->directoryEntry->fileSize);

}

void F16P_destroy(Fat16Partition* self)
{
    free(self->bootSector);
    free(self->allocationTables[0]);
    free(self->allocationTables[1]);
    free(self->directoryEntry);
    free(self);
}

void _InitializeBootSector(BootSector* self, FILE* file, int* offset)
{
    fpread(&self->jump, 3, 1, offset, file);
    fread(&self->name, 8, 1, file);
    fread(&self->bytesPerSector, 2, 1, file);
    fread(&self->sectorsPerCluster, 1, 1, file);
    fread(&self->reservedSectors, 2, 1, file);
    fread(&self->fatCopies, 1, 1, file);
    fread(&self->rootEntries, 2, 1, file);
    fread(&self->smallNumSectors, 2, 1, file);
    fread(&self->mediaDescriptor, 1, 1, file);
    fread(&self->sectorsPerTrack, 2, 1, file);
    fread(&self->numHeads, 2, 1, file);
    fread(&self->hiddenSectors, 4, 1, file);
    fread(&self->largeNumSectors, 4, 1, file);
    fread(&self->driveNumber, 1, 1, file);
    fread(&self->reserved, 1, 1, file);
    fread(&self->extendedBootSignature, 4, 1, file);
    fread(&self->volumeSerialNumber, 4, 1, file);
    fread(&self->volumeLabel, 11, 1, file);
    fread(&self->fileSystemType, 8, 1, file);
    fread(&self->bootstrapCode, 448, 1, file);
    fread(&self->signature, 2, 1, file);
}

void _InitializeAllocationTable(AllocationTable* self, FILE* file)
{
    fread(&self->entries, 256, 1, file);
}

void _InitializeDirectoryEntry(DirectoryEntry* self, FILE* file)
{
    fread(&self->name, 8, 1, file);
    fread(&self->extension, 3, 1, file);
    fread(&self->attributes, 1, 1, file);
    fread(&self->reserved, 1, 1, file);
    fread(&self->creationTime, 2, 1, file);
    fread(&self->creationDate, 2, 1, file);
    fread(&self->lastAccessDate, 2, 1, file);
    fread(&self->fat32Reserved, 2, 1, file);
    fread(&self->lastWriteTime, 2, 1, file);
    fread(&self->lastWriteDate, 2, 1, file);
    fread(&self->fileSize, 4, 1, file);
}
 */