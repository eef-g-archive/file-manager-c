#ifndef READABLE_H
#define READABLE_H
#include <stdint.h>

char* HumanSize(uint64_t size);
char* MediaType(uint8_t media);
char* FileAttributes(uint8_t byte);
char* PartitionType(uint8_t type);
char* VolumeLabel(uint8_t* label);
#endif
