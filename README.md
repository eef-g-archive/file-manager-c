# File Manager in C

This is a file manager that allows you to manage files on your computer. <br />
It provides an interface for you to view and organize files and folders on your computer.

## How to use

To use the file manager in your project, include commands.h, readable.h, reader.h, commands.c, readable.c, reader.c, runtime.c and Makefile files in your source code.

## Files included

### commands.h 
contains the declarations of the functions used in the commands.c file. 

### readable.h 
contains the declarations of the functions used in the readable.c file. 

### reader.h
This is a C header file that contains function prototypes and struct definitions. <br />
The header file is used to declare the functions and structs that are defined in the source file.

The header file contains the following:<br />
* Partition struct definition<br />
* MBR struct definition<br />
* FBoot struct definition<br />
* FATEntry typedef<br />
* FTable struct definition<br />
* RootEntry struct definition<br />
* RootDirectory struct definition<br />

Function prototypes for:<br />
* ReadDiskImage(char* path)<br />
* ParseMBR(FILE* disk, uint64_t offset)<br />
* ParseFBoot(FILE* disk, uint64_t offset)<br />
* ParseFTable(FILE* path, uint64_t offset)<br />

### commands.c

* The InputLoop(FILE* disk) function reads user input from the command line and executes the appropriate command. <br />
The function calls other functions such as PrintHelp(), ls(), cd(char* path), cat(char* path), and stats() depending on the user input.<br />
* The ls() function prints the contents of the current directory.<br />
* The cat(char* path) function reads a file from the disk and prints its contents.<br />

### readable.c

* The HumanSize(uint64_t size) function takes a size in bytes and returns a human-readable string representation of the size in bytes, kilobytes, megabytes, or gigabytes.<br />
* The FileAttributes(uint8_t byte) function takes a byte representing file attributes and returns a string representation of the attributes.<br />
* The PartitionType(uint8_t type) function takes a byte representing partition type and returns a string representation of the partition type.<br />

### reader.c

* The ReadDiskImage(char* path) function reads a disk image from the specified path and parses the MBR, boot sector, and FAT table.<br /> 
The function then saves the parsed data to global variables so that they can be used later.<br />
* The ParseMBR(FILE* disk, uint64_t offset) function reads an MBR from the specified disk and returns an MBR struct.<br />
* The ParseFBoot(FILE* path, uint64_t offset) function reads a boot sector from the specified path and returns a boot sector struct.<br />
* The ParseFTable(FILE* path, uint64_t offset, int count, int sectors, int sectorSize) function reads a FAT table from the specified path and returns an FTable struct.<br />
* The ParseRootDirectory(FILE* path, uint64_t offset, uint16_t entries) function reads a root directory from the specified path and returns a RootDirectory struct.<br />
* The SummarizeDisk() function prints out a summary of the disk’s file system information and root directory.<br />
* The lsPrint() function prints out the contents of the root directory.<br />

### runtime.c contains the main function for the program.

### The Makefile is used for compiling and linking the project.

## Compiling and running

To compile and run the project on Linux or macOS:
* Open a terminal window.
* Navigate to the directory where your file manager is located.
* Compile your file manager by running “make”.
* Run your file manager by running “./file-manager-c”.
