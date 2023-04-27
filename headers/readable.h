#ifndef READABLE_H
#define READABLE_H
#include <stdint.h>

char* HumanSize(uint64_t size);
char* FileAttributes(uint8_t byte);
char* PartitionType(uint8_t type);
char* VolumeLabel(uint8_t* label);
char* DriveLabel(uint8_t* label);
int DriveSerial(uint32_t* serial);
char* FileName(uint8_t* name, uint8_t* extension);
#endif
