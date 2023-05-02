#include "reader.h"
#include "commands.h"   

int main(int argc, char* argv[])
{ 
    if (argc < 2)
    {
        printf("Usage: %s <disk image>\n", argv[0]);
        return 1;
    }

    char* file = argv[1];

    fatDisk = file;
    ReadDiskImage(file);


    char input[BufferSize];
    char* command;
    char* token; 
    char* next_token; 
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