#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "reader.h"
#include "readable.h"
 
#define BufferSize 256  

typedef struct
{
    const char* command;
    void (*function)(int, char**);
    int argsCount;
} Command;

extern const Command Commands[];

static FILE* global_disk;
static uint32_t global_clusterOffset;
static _FBoot* global_fBoot;

 
void List();
void stats();
void ChangeDirectory(char* path);
void Concatenate(char* path);

extern void InitializeFileManager(char* disk);
extern int MainLoop();