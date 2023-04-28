#ifndef READER_H
#define READER_H

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

typedef struct _Partition
{
    uint8_t bootIndicator;
    uint8_t first_chs[3];
    uint8_t partitionType;
    uint8_t last_chs[3];
    uint32_t sectorOffset;
    uint32_t numSectors;

} __attribute__((packed)) Partition;

typedef struct _MBR
{
    uint8_t code[446];
    Partition partitions[4];
    uint16_t signature;

} __attribute__((packed)) MBR;

typedef struct _FBoot
{
    uint8_t jump[3];
    uint8_t oem[8]; // OEM name in ASCII

    // BIOS
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t fatCopies;
    uint16_t rootEntries;
    uint16_t logicalSectors;
    uint8_t mediaDescriptor;
    uint16_t sectorsPerFat;

    // DOS
    uint16_t sectorsPerTrack;
    uint16_t numHeads;
    uint8_t hiddenSectors[4];
    uint8_t totalLogicalSectors[4];

    // BIOS pt. 2
    uint8_t driveNumber;
    uint8_t reserved;
    uint8_t extendedBootSignature;
    uint32_t volumeSerialNumber;
    uint8_t volumeLabel[11];
    uint8_t fileSystemType[8];

    // Boot Code
    uint8_t bootCode[448];
    uint16_t signature;
} __attribute__((packed)) FBoot;

typedef uint16_t FATEntry;
typedef struct FTable
{
    FATEntry entries[0]; // Don't know how many entries we'll have until we parse the disk
} __attribute__((packed)) FTable;

typedef struct RootEntry
{
    uint8_t name[8];
    uint8_t extension[3];
    uint8_t attributes;
    uint8_t reserved[10];
    uint16_t timeLastChanged;
    uint16_t dateLastChanged;
    uint16_t startingCluster;
    uint32_t fileSize;
} __attribute__((packed)) RootEntry;

typedef struct RootDirectory
{
    RootEntry entries[0]; // Don't know how many entries we'll have until we parse the disk
} __attribute__((packed)) RootDirectory;

// Functions
int ReadDiskImage(char* path);
MBR* ParseMBR(FILE* disk, uint64_t offset);
FBoot* ParseFBoot(FILE* disk, uint64_t offset);
FTable* ParseFTable(FILE* path, uint64_t offset, int count, int sectors, int sectorSize);
RootDirectory* ParseRootDirectory(FILE* path, uint64_t offset, uint16_t entries);


// Print Functions
void SummarizeDisk();
void lsPrint(); // Currently only working with root directory
void catPrint(char* path); // Path will be the file name 
#endif