#include <stdio.h>
#include <stdlib.h>

#pragma region Resersved Sector Structs

typedef struct BootSector
{
    __uint16_t bytesPerSector;
    __uint8_t sectorsPerCluster;
    __uint16_t reservedSectors;
    __uint8_t fatCopies;
    __uint16_t rootEntries;
    __uint16_t totalSectors;
    __uint8_t mediaDescriptor;
    __uint16_t sectorsPerFAT;
    __uint16_t sectorsPerHead;
    __uint16_t headsPerCylinder;
    __uint32_t hiddenSectors;
    __uint32_t bigNumberofSectors;
    __uint32_t bigNumberSectorsPerFAT32;
    __uint16_t flags;
    __uint16_t version;
    __uint32_t rootCluster;
    __uint16_t fsInfoSector;
    __uint16_t backupBootSector;
    __uint8_t reserved[12];
} __attribute__ ((packed)) BootSector;

BootSector* BootSector_new(FILE* file, int offset);
void BootSector_init(BootSector* self, FILE* file, int offset);
void BootSector_print(BootSector* self);
void BootSector_destroy(BootSector* self);

// This is only used for FAT32
typedef struct FSInfo
{
    __uint32_t signature;
    __uint8_t reserved[480];
    __uint32_t signature2;
    __uint32_t freeClusterCount;
    __uint32_t nextFreeCluster;
    __uint8_t reserved2[12];
    __uint32_t signature3;
} __attribute__ ((packed)) FSInfo;

FSInfo* FSInfo_new(FILE* file, int offset);
void FSInfo_init(FSInfo* self, FILE* file, int offset);
void FSInfo_print(FSInfo* self);
void FSInfo_destroy(FSInfo* self);

typedef struct ReservedSectors
{
    BootSector* boot;
    FSInfo* fsInfo;
} __attribute__ ((packed)) ReservedSectors;

ReservedSectors* ReservedSectors_new(FILE* file, int offset);
void ReservedSectors_init(ReservedSectors* self, FILE* file, int offset);
void ReservedSectors_print(ReservedSectors* self);
void ReservedSectors_destroy(ReservedSectors* self);

#pragma endregion


#pragma region FAT Region Structs

typedef struct FTable
{

} FTable;

#pragma endregion

typedef struct Partition
{
    ReservedSectors* reserved;
    FTable* FTables[2]; // Use 2 tables bc of FAT redundancy

} __attribute__ ((packed)) Partition;

Partition* Partition_new(FILE* file, int offset);
void Partition_init(Partition* self, FILE* file, int offset);
void Partition_print(Partition* self);