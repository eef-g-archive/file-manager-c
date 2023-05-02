#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "reader.h"
#include "readable.h"

static FILE* global_disk;
static uint32_t global_clusterOffset;
static FBoot* global_fBoot;

void InputLoop(FILE* disk);
void PrintHelp();
void ls();
void stats();
void cd(char* path);
void cat(char* path);