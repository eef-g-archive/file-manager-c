#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../headers/readable.h"

char* HumanSize(uint64_t size)
{
    char* humanSize = (char*)malloc(12);
    memset(humanSize, 0, 12);
    if(size < 1024)
    {
        sprintf(humanSize, "%d B", size);
    }
    else if(size < 1048576)
    {
        sprintf(humanSize, "%d KB", size / 1024);
    }
    else if(size < 1073741824)
    {
        sprintf(humanSize, "%d MB", size / 1048576);
    }
    else
    {
        sprintf(humanSize, "%d GB", size / 1073741824);
    }
    return humanSize;
}


char* FileAttributes(uint8_t byte)
{
    char* attributes = (char*)malloc(12);
    memset(attributes, 0, 12);
    if(byte & 0x01)
    {
        strcat(attributes, "RO"); // Read Only
    }
    if(byte & 0x02)
    {
        strcat(attributes, "H"); // Hidden
    }
    if(byte & 0x04)
    {
        strcat(attributes, "S"); // System
    }
    if(byte & 0x08)
    {
        strcat(attributes, "V"); // Volume Label
    }
    if(byte & 0x10)
    {
        strcat(attributes, "Dir"); // Directory
    }
    if(byte & 0x20)
    {
        strcat(attributes, "A"); // Archive
    }
    if(byte & 0x40)
    {
        strcat(attributes, "D"); // Device
    }
    if(byte & 0x80)
    {
        strcat(attributes, "R"); // Reserved
    }
    return attributes;
}

char* PartitionType(uint8_t type)
{
    switch(type)
    {
        case 0x01:
        {
            return "FAT12";
            break;
        }
        case 0x04:
        {
            return "FAT16";
            break;
        }
        case 0x06:
        {
            return "FAT16B";
            break;
        }
        case 0x07:
        {
            return "NTFS";
            break;
        }
        case 0x0B:
        {
            return "FAT32 -- CHS";
            break;
        }
        case 0x0C:
        {
            return "FAT32 -- LBA";
            break;
        }
        case 0x0e:
        {
            return "FAT16 -- LBA";
            break;
        }
        default:
        {
            return "Unknown";
            break;
        }
    }
}

char* VolumeLabel(uint8_t* label)
{
    char* volumeLabel = (char*)malloc(12);
    memset(volumeLabel, 0, 12);
    memcpy(volumeLabel, label, 11);
    return volumeLabel;
}

char* DriveLabel(uint8_t* label)
{
    char* volumeLabel = (char*)malloc(12);
    memset(volumeLabel, 0, 12);
    memcpy(volumeLabel, label, 8);
    return volumeLabel;
}

int DriveSerial(uint32_t* serial)
{
    int serialNumber = 0;
    memcpy(&serialNumber, serial, 10);
    return serialNumber;
}