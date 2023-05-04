#include "commands.h"
#include "reader.h"    



void List()
{
    PrintDiskList();
}

void Concatenate(int argc, char* argv[])
{
    // Prep the argument for the command
    char* path = argv[1];

    char* pass = malloc(BufferSize);
    size_t len = strlen(path);
    strncpy_s(pass, BufferSize, path, len);

    // Send the file name to the command
    uint8_t* fileData = ReadFile(pass);
    printf("%x\n", fileData);
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