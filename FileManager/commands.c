#include "commands.h"
#include "reader.h"    



void List()
{
    PrintDiskList();
}

void Concatenate(char* path)
{
    // Get the root directory
    RootDirectory* root = ParseRootDirectory(fatDisk, fatClusterOffset, fatBoot->rootEntries);
    if(root == NULL)
    {
        printf("Error: Could not parse root directory!\n");
        return;
    }

    // Get the file
    RootEntry* file = NULL;
    for(int i = 0; i < fatBoot->rootEntries; i++)
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
    uint32_t clusterCount = fileSize / (fatBoot->bytesPerSector * fatBoot->sectorsPerCluster);

    // Get the file cluster offset
    uint32_t clusterOffset = cluster * fatBoot->bytesPerSector * fatBoot->sectorsPerCluster;

    // Get the file cluster remainder
    uint32_t clusterRemainder = fileSize % (fatBoot->bytesPerSector * fatBoot->sectorsPerCluster);

    // Get the file cluster remainder offset
    uint32_t clusterRemainderOffset = clusterOffset + (clusterCount * fatBoot->bytesPerSector * fatBoot->sectorsPerCluster);

    // Get the file cluster remainder count
    uint32_t clusterRemainderCount = clusterRemainder / fatBoot->bytesPerSector;

    // Get the file cluster remainder remainder
    uint32_t clusterRemainderRemainder = clusterRemainder % fatBoot->bytesPerSector;
}




void stats()
{
    SummarizeDisk();
}

void ChangeDirectoryCommand(int argc, char* argv[])
{
    char* path = argv[1];

    char* pass = malloc(BufferSize);
    size_t len = strlen(path);
    strncpy_s(pass, BufferSize, path, len);

    ChangeDirectory(pass);
}

void HelpCommand(int argc, char* argv[])
{
    printf("Available commands:\n");
    printf("  ls [path]                 - ls \n");
    printf("  cat [path]                - cat\n");
    printf("  cd [path]                 - cd\n");
    printf("  print                     - print \n");
    printf("  help                      - Show this help message\n");
    printf("  exit                      - Exit the program\n");
} 

const Command Commands[] = {
    {"ls", List, 0}, 
    {"stats", stats, 0}, 
    {"cat", Concatenate, 1}, 
    {"cd", ChangeDirectoryCommand, 1}, 
    {"print", PrintDiskList, 0},
    {"help", HelpCommand, 0}, 
    {"exit", NULL, 0}, 
};

void ExecuteCommand(const char* command, int argc, char* argv[])
{
    int commandCount = sizeof(Commands) / sizeof(Command);
    int commandFound = 0;

    for (int i = 0; i < commandCount; i++)
    {
        if (strcmp(Commands[i].command, command) == 0)
        {
            commandFound = 1;
            if (Commands[i].function != NULL)
            {
                if (argc - 1 == Commands[i].argsCount)
                {
                    Commands[i].function(argc, argv);
                }
                else
                {
                    if (Commands[i].argsCount == -1)
                        Commands[i].function(argc, argv);
                    else
                        printf("Incorrect number of arguments for command: %s\n", command);
                }
            }
            break;
        }
    }

    if (!commandFound)
    {
        printf("Command not found: %s\n", command);
        printf("    type \"help\" for the list commands.\n");
    }
} 