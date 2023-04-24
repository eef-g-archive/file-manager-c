/*
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#pragma region Resersved Sector Structs

typedef struct BootSector
{
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t fatCopies;
    uint16_t rootEntries;
    uint16_t totalSectors;
    uint8_t mediaDescriptor;
    uint16_t sectorsPerFAT;
    uint16_t sectorsPerHead;
    uint16_t headsPerCylinder;
    uint32_t hiddenSectors;
    uint32_t bigNumberofSectors;
    uint32_t bigNumberSectorsPerFAT32;
    uint16_t flags;
    uint16_t version;
    uint32_t rootCluster;
    uint16_t fsInfoSector;
    uint16_t backupBootSector;
    uint8_t reserved[12];
} __attribute__ ((packed)) BootSector;

BootSector* BootSector_new(FILE* file, int* offset);
void BootSector_init(BootSector* self, FILE* file, int* offset);
void BootSector_print(BootSector* self);
void BootSector_destroy(BootSector* self);

// This is only used for FAT32
typedef struct FSInfo
{
    uint32_t signature;
    uint8_t reserved[480];
    uint32_t signature2;
    uint32_t freeClusterCount;
    uint32_t nextFreeCluster;
    uint8_t reserved2[12];
    uint32_t signature3;
} __attribute__ ((packed)) FSInfo;

FSInfo* FSInfo_new(FILE* file, int* offset);
void FSInfo_init(FSInfo* self, FILE* file, int* offset);
void FSInfo_print(FSInfo* self);
void FSInfo_destroy(FSInfo* self);

typedef struct ReservedSectors
{
    BootSector* boot;
    FSInfo* fsInfo;
} __attribute__ ((packed)) ReservedSectors;

ReservedSectors* ReservedSectors_new(FILE* file, int* offset, int isFAT32);
void ReservedSectors_init(ReservedSectors* self, FILE* file, int* offset, int isFAT32);
void ReservedSectors_print(ReservedSectors* self);
void ReservedSectors_destroy(ReservedSectors* self);

#pragma endregion


#pragma region FAT Region Structs

typedef struct FTable
{
  uint32_t entries[2048];
} FTable;

FTable* FTable_new(FILE* file);
void FTable_init(FTable* self, FILE* file);
void FTable_destroy(FTable* self);

#pragma endregion

typedef struct Part
{
    ReservedSectors* reserved;
    FTable* tables[2]; // Use 2 tables bc of FAT redundancy

} __attribute__ ((packed)) Partition;

Partition* Partition_new(FILE* file, int* offset, int isFAT32);
void Partition_init(Partition* self, FILE* file, int* offset, int isFAT32);
void Partition_print(Partition* self);

*/