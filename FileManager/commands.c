#include "commands.h"
#include "reader.h"   

void List()
{
    PrintDiskList();
}

void Concatenate(char* path)
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

void ChangeDirectory(char* path)
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
    {"cat", Concatenate, 0}, 
    {"cd", ChangeDirectory, 1}, 
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

void InitializeFileManager(char* disk)
{
    global_disk = disk;
    ReadDiskImage(disk); 
}

int MainLoop()
{ 
    char input[BufferSize];
    char* command;
    char* token;
    char* argv[BufferSize];
    char* next_token;
    int argc;

    while (1)
    {
        printf("Enter a command and arguments: ");
        if (fgets(input, BufferSize, stdin) == NULL)
        {
            printf("fgets failed\n");
            continue;
        }

        // Remove newline character from the input string
        input[strcspn(input, "\n")] = 0;

        command = strtok_s(input, " ", &next_token);

        if (command == NULL)
        {
            printf("No command entered. Type help for commands.\n");
            continue;
        }

        argc = 0;
        argv[argc++] = command; // Add the command as the first argument
        token = strtok_s(NULL, " ", &next_token);

        while (token != NULL)
        {
            argv[argc++] = token;
            token = strtok_s(NULL, " ", &next_token);
        }

        if (strcmp(command, "exit") == 0) break; 
        else ExecuteCommand(command, argc, argv); 
    }

    return 0;
}