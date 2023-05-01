# File Manager in C

This is a file manager that allows you to manage files on your computer.
It provides an interface for you to view and organize files and folders on your computer.

## How to use

To use the file manager in your project, include commands.h, readable.h, reader.h, commands.c, readable.c, reader.c, runtime.c and Makefile files in your source code.

## Files included

### commands.h 

contains the declarations of the functions used in the commands.c file. 

### readable.h 

contains the declarations of the functions used in the readable.c file. 

### reader.h

This is a C header file that contains function prototypes and struct definitions. 

The header file is used to declare the functions and structs that are defined in the source file.

The header file contains the following:

Partition struct definition

MBR struct definition

FBoot struct definition

FATEntry typedef

FTable struct definition

RootEntry struct definition

RootDirectory struct definition

Function prototypes for:

ReadDiskImage(char* path)

ParseMBR(FILE* disk, uint64_t offset)

ParseFBoot(FILE* disk, uint64_t offset)

ParseFTable(FILE* path, uint64_t offset)

### The commands.c file contains the implementation of command functions. 

### The readable.c file contains the implementation of read functions. 

### The reader.c file contains the implementation of read functions. 

### The runtime.c file contains the implementation of runtime functions. 

### The Makefile is used for compiling and linking the project.

## Compiling and running

To compile and run the project on Linux or macOS:
-Open a terminal window.
-Navigate to the directory where your file manager is located.
-Compile your file manager by running “make”.
-Run your file manager by running “./file-manager-c”.
