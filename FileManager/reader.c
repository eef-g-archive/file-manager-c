#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "reader.h"
#include "readable.h"

static FILE* disk;
static FTable* table;
static uint32_t clusterOffset;
static _FBoot* global_fBoot;
static RootDirectory global_rootDir;
static _MBR* global_mbr;
static int global_partitionOffset;

int ReadDiskImage(char* path)
{  
    FILE* file = NULL;

    // Open file in binary mode
    errno_t err = fopen_s(&file, path, "rb");

    disk = file;
    if(disk == NULL)
    {
        printf("Error: Could not open disk image '%s'.\n", path);
        return 1;
    }

    // Parse the MBR

    _MBR * tMBR = ParseMBR(disk, 0);
    global_mbr = tMBR;

    if (tMBR == NULL)
    {
        printf("Error: Could not parse MBR!\n");
        return 1;
    }

    // Parse the Boot Sector
    int offset = 0;
    int partitions = 0;
    global_partitionOffset = 0;
    // Go through each potential partition and then check if it's FAT32 or FAT16 then update the offset of where the boot sector is
    for(int i = 0; i < 4; i++)
    {
        if(global_mbr->partitions[i].partitionType == 0x0e || global_mbr->partitions[i].partitionType == 0x0c)
        {
            if (offset == 0)
            {
                offset = global_mbr->partitions[i].sectorOffset * 512;
            }
                
            partitions++;
        }
    }

    if (offset == 0)
    {
        printf("Error: Could not find a valid partition in the MBR!\n");
        return 1;
    }

    // Using the offset, parse the boot sector
    // Save the bootsector to a global variable so we can refer to it later (Mainly in the runtime.c file)
    _FBoot * tBoot = ParseFBoot(disk, offset);
    global_fBoot = tBoot;
    

    // Parse the FAT Table
    // First, get the info we need from the boot sector
    int count = global_fBoot->fatCopies;
    int sectors = global_fBoot->sectorsPerFat;
    int sectorSize = global_fBoot->bytesPerSector;
    int FATOffset = offset + (global_fBoot->reservedSectors * sectorSize);

    // FAT Table debugging
    //printf("Table Count: %d\nNumber of Sectors: %d\nSector Size: %d\nFAT Offset: %d\n", count, sectors, sectorSize, FATOffset);
    
    // Then, parse the FAT Table
    FTable * tFatTable = ParseFTable(disk, FATOffset, count, sectors, sectorSize);
    table = tFatTable;
    if(tFatTable == NULL)
    {
        printf("Error: Could not parse FAT Table!\n");
        return 1;
    }

    // Parse the Root Directory
    // First, find out the offset to the root directory

    int offsetToRoot = FATOffset + (count * sectors * sectorSize);
    global_partitionOffset = offsetToRoot;

    // Should be -- 1314816
    // Then, parse the root directory
    RootDirectory tempRoot = ParseRootDirectory(disk, offsetToRoot); 
    RootDirectory* tRoot = &tempRoot;
    global_rootDir = tempRoot;

    if(tRoot == NULL)
    {
        printf("Error: Could not parse root directory!\n");
        return 1;
    }
    clusterOffset = offsetToRoot + (global_fBoot->rootEntries * sizeof(RootEntry));
    global_partitionOffset = clusterOffset;
    //SummarizeDisk(_MBR);
    return 0;
}



// _MBR Parsing --------------------------------------------------------------------------------------------------
_MBR* ParseMBR(FILE* disk, uint64_t offset)
{
    int seek = fseek(disk, offset, SEEK_SET); // Move the file reader to the correct offset (even though it will be 0)
    if(seek != 0)
    {
        printf("Error: Could not seek to offset!");
        return NULL;
    }

    // Create a buffer to read the MBR into -- This lets us throw away the buffer if it's not valid
    // Think of the buffer as a form of error checking for creating the MBR
    char* buffer = (char*)malloc(sizeof(_MBR));
    int totalRead = fread(buffer, 1, sizeof(_MBR), disk);
    if(totalRead != sizeof(_MBR))
    {
        printf("Error: Could not read _MBR!");
        return NULL;
    }

    return (_MBR*)buffer; // Convert the bufer to an _MBR struct but ONLY if valid buffer!
}



// FATBoot Parsing --------------------------------------------------------------------------------------------------
_FBoot* ParseFBoot(FILE* path, uint64_t offset)
{
    int seek = fseek(path, offset, SEEK_SET);
    if(seek != 0)
    {
        printf("Error: Could not seek to offset!");
        return NULL;
    }

    // Create a buffer to read the boot sector into -- This lets us throw away the buffer if it's not valid
    // Think of the buffer as a form of error checking for creating the boot sector
    char* buffer = (char*)malloc(sizeof(_FBoot));
    int totalRead = fread(buffer, 1, sizeof(_FBoot), path);
    if(totalRead != sizeof(_FBoot))
    {
        printf("Error: Could not read boot sector!");
        return NULL;
    }

    return buffer; // Convert the buffer to a boot sector struct but ONLY if valid buffer!
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
    int size = count * (sectors * sectorSize);

    char* buffer = (char*)malloc(size);

    int totalRead = fread(buffer, 1, size, path);
    if(totalRead < size)
    {
        printf("Error: Could not read FAT Table!");
        free(buffer); // Free the buffer if we can't read it -- Avoids a memory leak
        return NULL;
    }
    return (FTable*)buffer;
}


// Root Directory Parsing --------------------------------------------------------------------------------------------------
RootDirectory ParseRootDirectory(FILE* path, uint64_t offset)
{
    RootDirectory dir;
    int idx = 0;
    RootEntry tmp;
    dir.entries = malloc(sizeof(RootEntry) * 512);
    fseek(path, offset, SEEK_SET);
    while (true)
    {
        fread(&tmp, sizeof(RootEntry), 1, path);
        if (tmp.name[0] != 0x00)
        {
            if (tmp.name[0] != 0xE5)
            {
                // Now actually parse the Root Entry
                memcpy(&dir.entries[idx], &tmp, sizeof(RootEntry));
                idx++;
            }
        }
        else
        {
            break;
        }
    }
    dir.numberEntries = idx;
    return dir;
    /*
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
    */
} 


/*
    TODO: 
    1. Get a Root Entry
    2. Get a Directory Size ( Can probably do this from the root entry )
*/ 


/*
----------------------------------------------------
                Print Functions
----------------------------------------------------
*/

// Print the MBR
void SummarizeDisk()
{
    _MBR* mbr = global_mbr;
    printf("-=| File System Information |=-\n");
    printf("----------------------------------------------\n");
    printf("| #\t| Name\t| Serial\t| Size\t| Type\t|\n");
    int validPartition = 1;
    for(int i = 0; i < 4; i++)
    {
        if(mbr->partitions[i].partitionType == 0x0e || mbr->partitions[i].partitionType == 0x0c)
        {
            printf("Start Partition %d\n", i);
            // Get the boot sector for the partition
            _FBoot* boot = ParseFBoot(disk, mbr->partitions[i].sectorOffset * 512);

            printf("| %d\t", validPartition);
            printf("| %s\t", DriveLabel(boot->volumeLabel));

            printf("| %d\t", boot->volumeSerialNumber);
            printf("| %s\t", HumanSize(boot->bytesPerSector * boot->sectorsPerFat));
            printf("| %s |\n", PartitionType(mbr->partitions[i].partitionType));
            validPartition++;
            printf("\n", i);
        }

    }
    printf("----------------------------------------------\n");
    printf("-=| Root Directory |=-\n");
    printf("----------------------------------------------\n");
    printf("| #\t| Name\t| Size\t| Attributes\t|\n");
    for(int i = 0; i < global_fBoot->rootEntries; i++)
    {
        if(global_rootDir.entries[i].name[0] != 0x00 && global_rootDir.entries[i].name[0] != 0xe5)
        {
            printf("| %d\t", i);
            printf("| %s\t", FileName(global_rootDir.entries[i].name, global_rootDir.entries[i].extension));
            printf("| %s\t", HumanSize(global_rootDir.entries[i].fileSize));
            printf("| %s\t|\n", FileAttributes(global_rootDir.entries[i].attributes));
        }
    }
}


void PrintDiskList()
{
    RootDirectory root = global_rootDir;
    for(int i = 0; i < root.numberEntries; i++)
    {
        if(root.entries[i].attributes == 0x0F)
        {
            continue;
        }
        else if (root.entries[i].attributes == 0x08)
        {
            continue;
        }
        else if (IsDirectory(root.entries[i].attributes))
        {
            printf("%s\n", DirectoryName(root.entries[i].name));
        }
        else
        {
            if(root.entries[i].attributes == 0x10)
            {
                printf("%s\n", FileName(root.entries[i].name, root.entries[i].extension));
            }
            else
            {
                printf("%s\n", FileName(root.entries[i].name, root.entries[i].extension));
            }
        }
    }
}


void ChangeDirectory(char* path)
{
    // Get the root directory

    //_FBoot* boot = ParseFBoot(fatDisk, fatMBR->partitions[i].sectorOffset * 512);
    RootDirectory root = global_rootDir;//ParseRootDirectory(disk, clusterOffset, global_fBoot->rootEntries)
    
    // Get the directory
    RootEntry* dir = NULL;
    for (int i = 0; i < global_fBoot->rootEntries; i++)
    {
        RootEntry curr = root.entries[i];
        if (curr.name[0] == 0x00)
            continue;

        else if (curr.name[0] == 0xE5)
            continue;

        else if (curr.attributes == 0x0F)
            continue; 
        else
        { 

            char* fileName;

            if (IsDirectory(curr.attributes)) fileName = DirectoryName(curr.name);
            else fileName = FileName(root.entries[i].name, root.entries[i].extension);

            if (strcmp(path, fileName) == 0)
            {
                dir = &root.entries[i];
                break;
            }
        }
    }

    // Check if the directory exists
    if (dir == NULL)
    {
        printf("Error: Directory '%s' does not exist!\n", path);
        return;
    }


    // Set up the cluster and change the formula to get to a cluster depending on where we're going
    // I.E. if we're going to the .. directory, then don't -2 the cluster number
    uint32_t cluster = 0;
    if (strcmp("..", path) == 0)
        cluster = global_partitionOffset + ((dir->startingCluster) * 4 * 512);
    else
		cluster = global_partitionOffset + ((dir->startingCluster - 2) * 4 * 512);

    

    // Get the directory cluster offset
    //uint32_t newClusterOffset = cluster * global_fBoot->bytesPerSector * global_fBoot->sectorsPerCluster;

    // Set the global cluster offset
    clusterOffset = cluster;


    global_rootDir = ParseRootDirectory(disk, clusterOffset);


    
    for (int i = 0; i < global_fBoot->rootEntries; i++)
    {

    }
}
