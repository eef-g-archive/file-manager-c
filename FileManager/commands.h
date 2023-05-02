#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "reader.h"
#include "readable.h"
 
#define BufferSize 256   

static FILE* fatDisk;
static FTable* fatTable;
static uint32_t fatClusterOffset;
static _FBoot* fatBoot;
static RootDirectory* fatRootDir;
static _MBR* fatMBR;

typedef struct
{
    const char* command;
    void (*function)(int, char**);
    int argsCount;
} Command;

extern const Command Commands[];  
 
void List();
void stats();

void ChangeDirectoryCommand(int argc, char* argv[]);

void Concatenate(char* path);
 