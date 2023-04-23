#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../headers/reader.h"
#include "../headers/readable.h"

static FILE* disk;
static FTable* table;
static uint32_t clusterOffset;
static FBoot* global_fBoot;
static RootDirectory* global_rootDir;

int ReadDiskImage(char* path)
{
    FILE* file = fopen(path, "rb");
    disk = file;
    if(disk == NULL)
    {
        printf("Error: Could not open disk image '%s'.\n", path);
        return 1;
    }

    // Parse the MBR
    MBR* mbr = ParseMBR(disk, 0);
    if(mbr == NULL)
    {
        printf("Error: Could not parse MBR!\n");
        return 1;
    }

    // Parse the Boot Sector
    int offset = 0;
    int partitions = 0;
    // Go through each potential partition and then check if it's FAT32 or FAT16 then update the offset of where the boot sector is
    for(int i = 0; i < 4; i++)
    {
        if(mbr->partitions[i].partitionType == 0x0e || mbr->partitions[i].partitionType == 0x0c)
        {
            offset = mbr->partitions[i].sectorOffset * 512;
            partitions++;
        }
    }
    printf("Parsed %d partitions.\n", partitions);

    if (offset == 0)
    {
        printf("Error: Could not find a valid partition in the MBR!\n");
        return 1;
    }

    // Using the offset, parse the boot sector
    // Save the bootsector to a global variable so we can refer to it later (Mainly in the runtime.c file)
    FBoot* boot = ParseFBoot(disk, offset);
    printf("Boot sector parsed!\n");
    global_fBoot = boot;
    

    // Parse the FAT Table
    // First, get the info we need from the boot sector
    int count = boot->fatCopies;
    int sectors = boot->logicalSectors;
    int sectorSize = boot->bytesPerSector;
    int FATOffset = offset + (boot->reservedSectors * sectorSize);

    // FAT Table debugging
    printf("Table Count: %d\nNumber of Sectors: %d\nSector Size: %d\nFAT Offset: %d\n", count, sectors, sectorSize, FATOffset);
    // Then, parse the FAT Table
    FTable* fatTable = ParseFTable(disk, FATOffset, count, sectors, sectorSize);
    table = fatTable;
    if(fatTable == NULL)
    {
        printf("Error: Could not parse FAT Table!\n");
        return 1;
    }
    printf("FAT Table parsed!\n");

    // Parse the Root Directory
    // First, find out the offset to the root directory
    int offsetToRoot = FATOffset + (count * sectors * sectorSize);

    // Then, parse the root directory
    RootDirectory* rootDir = ParseRootDirectory(disk, offsetToRoot, boot->rootEntries);
    global_rootDir = rootDir;
    if(rootDir == NULL)
    {
        printf("Error: Could not parse root directory!\n");
        return 1;
    }
    clusterOffset = offsetToRoot + (boot->rootEntries * sizeof(RootEntry));

    printf("Root directory parsed!\n");
    return 0;
}



// MBR Parsing --------------------------------------------------------------------------------------------------
MBR* ParseMBR(FILE* disk, uint64_t offset)
{
    int seek = fseek(disk, offset, SEEK_SET); // Move the file reader to the correct offset (even though it will be 0)
    if(seek != 0)
    {
        printf("Error: Could not seek to offset!");
        return NULL;
    }

    // Create a buffer to read the MBR into -- This lets us throw away the buffer if it's not valid
    // Think of the buffer as a form of error checking for creating the MBR
    char* buffer = (char*)malloc(sizeof(MBR));
    int totalRead = fread(buffer, 1, sizeof(MBR), disk);
    if(totalRead != sizeof(MBR))
    {
        printf("Error: Could not read MBR!");
        return NULL;
    }

    return(MBR*)buffer; // Convert the bufer to an MBR struct but ONLY if valid buffer!
}



// FATBoot Parsing --------------------------------------------------------------------------------------------------
FBoot* ParseFBoot(FILE* path, uint64_t offset)
{
    int seek = fseek(path, offset, SEEK_SET);
    if(seek != 0)
    {
        printf("Error: Could not seek to offset!");
        return NULL;
    }

    // Create a buffer to read the boot sector into -- This lets us throw away the buffer if it's not valid
    // Think of the buffer as a form of error checking for creating the boot sector
    char* buffer = (char*)malloc(sizeof(FBoot));
    int totalRead = fread(buffer, 1, sizeof(FBoot), path);
    if(totalRead != sizeof(FBoot))
    {
        printf("Error: Could not read boot sector!");
        return NULL;
    }

    return(FBoot*)buffer; // Convert the buffer to a boot sector struct but ONLY if valid buffer!
}



// FAT Table Parsing --------------------------------------------------------------------------------------------------
FTable* ParseFTable(FILE* path, uint64_t offset, int count, int sectors, int sectorSize)
{
    int seek = fseek(path, offset, SEEK_SET);
    if(seek != 0)
    {
        printf("Error: Could not seek to FAT Table offset!");
        return NULL;
    }

    // Calculate the size of the FAT Table
    int size = count*(sectors * sectorSize);

    char* buffer = (char*)malloc(size);
    if(buffer == NULL)
    {
        printf("Error: Could not allocate memory for FAT Table buffer!");
        return NULL;
    }

    int totalRead = fread(buffer, 1, sizeof(sectorSize), path);
    if(totalRead <= size )
    {
        printf("Error: Could not read FAT Table!");
        free(buffer); // Free the buffer if we can't read it -- Avoids a memory leak
        return NULL;
    }
    return (FTable*)buffer;
}


// Root Directory Parsing --------------------------------------------------------------------------------------------------
RootDirectory* ParseRootDirectory(FILE* path, uint64_t offset, uint16_t entries)
{
    int size = entries * sizeof(RootEntry);

    char* buffer = (char*)malloc(size);
    if(buffer == NULL)
    {
        printf("Error: Could not allocate memory for root directory buffer!");
        return NULL;
    }

    int seek = fseek(path, offset, SEEK_SET);
    if(seek != 0)
    {
        printf("Error: Could not seek to root directory offset!");
        return NULL;
    }

    int totalRead = fread(buffer, 1, size, path);
    if(totalRead != size)
    {
        printf("Error: Could not read root directory!");
        free(buffer); // Free the buffer if we can't read it -- Avoids a memory leak
        return NULL;
    }
    return (RootDirectory*)buffer;
}