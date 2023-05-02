#include "commands.h"
#include "reader.h"

void InputLoop(FILE* disk)
{
    global_disk = disk;
    ReadDiskImage(disk);
    char * input = (char * )malloc(256);
    memset(input, 0, 256);
    while(1)
    {

        printf("> ");
        fgets(input, 256, stdin);
        input[strlen(input) - 1] = '\0';

        if(strcmp(input, "exit") == 0)
        {
            break;
        }
        else if(strcmp(input, "help") == 0)
        {
            PrintHelp();
        }
        else if(strcmp(input, "ls") == 0)
        {
            ls();
        }
        else if(strncmp(input, "cd", 2) == 0)
        {
            char* path = (char*)malloc(256);
            memset(path, 0, 256);
            strcpy(path, input + 3);
            cd(path);
        }
        else if(strncmp(input, "cat", 3) == 0)
        {
            char* path = (char*)malloc(256);
            memset(path, 0, 256);
            strcpy(path, input + 4);
            cat(path);
        }
        else if (strncmp(input, "stats", 5) == 0)
        {
            char* path = (char*)malloc(256);
            memset(path, 0, 256);
            strcpy(path, input + 6);
            stats(path);
        }
        else if(strncmp(input, "exit", 4) == 0)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Unknown command '%s'.\n", input);
        }

    }
}


void ls()
{
    lsPrint();
}

void cat(char* path)
{
    // Get the root directory
    RootDirectory* root = ParseRootDirectory(global_disk, global_clusterOffset, global_fBoot->rootEntries);
    if(root == NULL)
    {
        printf("Error: Could not parse root directory!\n");
        return;
    }

    // Get the file
    RootEntry* file = NULL;
    for(int i = 0; i < global_fBoot->rootEntries; i++)
    {
        if(root->entries[i].name[0] == 0x00)
        {
            continue;
        }
        else if(root->entries[i].name[0] == 0xE5)
        {
            continue;
        }
        else if(root->entries[i].attributes == 0x0F)
        {
            continue;
        }
        else
        {
            if(strcmp(path, FileName(root->entries[i].name, root->entries[i].extension)) == 0)
            {
                file = &root->entries[i];
                break;
            }
        }
    }

    // Check if the file exists
    if(file == NULL)
    {
        printf("Error: File '%s' does not exist!\n", path);
        return;
    }

    // Get the file size
    uint32_t fileSize = file->fileSize;

    // Get the file cluster
    uint32_t cluster = file->startingCluster;

    // Get the file cluster count
    uint32_t clusterCount = fileSize / (global_fBoot->bytesPerSector * global_fBoot->sectorsPerCluster);

    // Get the file cluster offset
    uint32_t clusterOffset = cluster * global_fBoot->bytesPerSector * global_fBoot->sectorsPerCluster;

    // Get the file cluster remainder
    uint32_t clusterRemainder = fileSize % (global_fBoot->bytesPerSector * global_fBoot->sectorsPerCluster);

    // Get the file cluster remainder offset
    uint32_t clusterRemainderOffset = clusterOffset + (clusterCount * global_fBoot->bytesPerSector * global_fBoot->sectorsPerCluster);

    // Get the file cluster remainder count
    uint32_t clusterRemainderCount = clusterRemainder / global_fBoot->bytesPerSector;

    // Get the file cluster remainder remainder
    uint32_t clusterRemainderRemainder = clusterRemainder % global_fBoot->bytesPerSector;
}

void stats()
{
    SummarizeDisk();
}

void cd(char* path)
{
    // Get the root directory
    RootDirectory* root = ParseRootDirectory(global_disk, global_clusterOffset, global_fBoot->rootEntries);
    if(root == NULL)
    {
        printf("Error: Could not parse root directory!\n");
        return;
    }

    // Get the directory
    RootEntry* dir = NULL;
    for(int i = 0; i < global_fBoot->rootEntries; i++)
    {
        if(root->entries[i].name[0] == 0x00)
        {
            continue;
        }
        else if(root->entries[i].name[0] == 0xE5)
        {
            continue;
        }
        else if(root->entries[i].attributes == 0x0F)
        {
            continue;
        }
        else
        {
            if(strcmp(path, FileName(root->entries[i].name, root->entries[i].extension)) == 0)
            {
                dir = &root->entries[i];
                break;
            }
        }
    }

    // Check if the directory exists
    if(dir == NULL)
    {
        printf("Error: Directory '%s' does not exist!\n", path);
        return;
    }

    // Get the directory cluster
    uint32_t cluster = dir->startingCluster;

    // Get the directory cluster offset
    uint32_t clusterOffset = cluster * global_fBoot->bytesPerSector * global_fBoot->sectorsPerCluster;

    // Set the global cluster offset
    global_clusterOffset = clusterOffset;
}

void PrintHelp()
{
    printf("Commands:\n");
}