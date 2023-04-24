// #include <stdint.h>


// #include <intty

// pes.h>
// #include <stdio.h>
// #include "utility.h"

// typedef struct BootSector
// {
//   uint8_t jump[3];
//   uint64_t name;
//   uint16_t bytesPerSector;
//   uint8_t sectorsPerCluster;
//   uint16_t reservedSectors;
//   uint8_t fatCopies;
//   uint16_t rootEntries;
//   uint16_t smallNumSectors; // Only used if the volume size is < 32MB
//   uint8_t mediaDescriptor;
//   uint16_t sectorsPerFat;
//   uint16_t sectorsPerTrack;
//   uint16_t numHeads;
//   uint32_t hiddenSectors;
//   uint32_t largeNumSectors; // Only used if the volume size is > 32MB
//   uint8_t driveNumber;
//   uint8_t reserved;
//   uint8_t extendedBootSignature;
//   uint32_t volumeSerialNumber;
//   uint8_t volumeLabel[11];
//   uint64_t fileSystemType;
//   uint8_t bootstrapCode[448];
//   uint16_t signature;
// } __attribute__ ((packed)) BootSector;

// typedef struct AllocationTable
// {
//   uint16_t entries[256];
// } __attribute__((packed)) AllocationTable;

// typedef struct DirectoryEntry
// {
//   uint8_t name[8];
//   uint8_t extension[3];
//   uint8_t attributes;
//   uint8_t reserved;
//   uint8_t creationTimeMilliseconds;
//   uint16_t creationTime;
//   uint16_t creationDate;
//   uint16_t lastAccessDate;
//   uint16_t fat32Reserved;
//   uint16_t lastWriteTime;
//   uint16_t lastWriteDate;
//   uint16_t startingCluster;
//   uint32_t fileSize;
// } __attribute__ ((packed)) DirectoryEntry;

// typedef struct Fat16Partition
// {
//   BootSector* bootSector;
//   AllocationTable* allocationTables[2];
//   DirectoryEntry* directoryEntry;
// } Fat16Partition;


// Fat16Partition* F16P_new(FILE* file, int* offset);
// void F16P_init(Fat16Partition* self, FILE* file, int* offset);
// void F16P_print(Fat16Partition* self);
// void F16P_destroy(Fat16Partition* self);

// void _InitializeBootSector(BootSector* self, FILE* file, int* offset);
// void _InitializeAllocationTable(AllocationTable* self, FILE* file);
// void _InitializeDirectoryEntry(DirectoryEntry* self, FILE* file);