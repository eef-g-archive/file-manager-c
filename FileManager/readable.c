#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "readable.h"

char* HumanSize(uint64_t size)
{
    char* humanSize = (char*)malloc(12 * sizeof(char));
    if (humanSize == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(humanSize, 0, 12);
    if (size < 1024)
    {
        sprintf_s(humanSize, 12, "%llu B", size);
    }
    else if (size < 1048576)
    {
        sprintf_s(humanSize, 12, "%llu KB", size / 1024);
    }
    else if (size < 1073741824)
    {
        sprintf_s(humanSize, 12, "%llu MB", size / 1048576);
    }
    else
    {
        sprintf_s(humanSize, 12, "%llu GB", size / 1073741824);
    }
    return humanSize;
}


char* FileAttributes(uint8_t byte)
{
    char* attributes = (char*)malloc(12 * sizeof(char));
    if (attributes == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(attributes, 0, 12);
    if (byte & 0x01)
    {
        strcat_s(attributes, 12, "RO"); // Read Only
    }
    if (byte & 0x02)
    {
        strcat_s(attributes, 12, "H"); // Hidden
    }
    if (byte & 0x04)
    {
        strcat_s(attributes, 12, "S"); // System
    }
    if (byte & 0x08)
    {
        strcat_s(attributes, 12, "V"); // Volume Label
    }
    if (byte & 0x10)
    {
        strcat_s(attributes, 12, "Dir"); // Directory
    }
    if (byte & 0x20)
    {
        strcat_s(attributes, 12, "A"); // Archive
    }
    if (byte & 0x40)
    {
        strcat_s(attributes, 12, "D"); // Device
    }
    if (byte & 0x80)
    {
        strcat_s(attributes, 12, "R"); // Reserved
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
    char* volumeLabel = (char*)malloc(12 * sizeof(char));
    if (volumeLabel == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(volumeLabel, 0, 12);
    memcpy_s(volumeLabel, 12, label, 11);
    return volumeLabel;
}

char* DriveLabel(uint8_t* label)
{
    char* volumeLabel = (char*)malloc(12 * sizeof(char));
    if (volumeLabel == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(volumeLabel, 0, 12);
    memcpy_s(volumeLabel, 12, label, 8);
    return volumeLabel;
}

int DriveSerial(uint32_t* serial)
{
    int serialNumber = 0;
    memcpy(&serialNumber, serial, 10);
    return serialNumber;
}


bool IsDirectory(uint8_t attribute) 
{
    return (attribute & 0x10) != 0 ? true : false; 
}

char* FileName(uint8_t* name, uint8_t* extension)
{
    char* fileName = (char*)malloc(13 * sizeof(char));
    if (fileName == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    //memset(fileName, 0, 13);
    //memcpy_s(fileName, 9, name, 8);
    strcpy_s(fileName, 13, DirectoryName(name));

    strcat_s(fileName, 13, ".");
    int strLength = strnlen_s(fileName, 8);
    for (int i = 0; i < 4; i++)
    {
        if ((char)extension[i] == ' ')
        {
            if (i == 0) return fileName;
            fileName[i + strLength] = '\0';
            return fileName;
        }
        else fileName[i + strLength] = extension[i];
    }
    fileName[12] = '\0';
    return fileName;
}

char* DirectoryName(uint8_t* name)
{
    char* dirName = (char*)malloc(13 * sizeof(char));
    if (dirName == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(dirName, 0, 13);
    memcpy_s(dirName, 9, name, 8); 

    int lastIndex = -1;
    for (int i = 0; i < 8; i++) {
        if (dirName[i] != ' ') {
            lastIndex = i;
        }
    } 
    if (lastIndex >= 0) {
        dirName[lastIndex + 1] = '\0';
    }

    return dirName;
}