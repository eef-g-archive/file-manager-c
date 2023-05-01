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
-Partition struct definition<br />
-MBR struct definition<br />
-FBoot struct definition<br />
-FATEntry typedef<br />
-FTable struct definition<br />
-RootEntry struct definition<br />
-RootDirectory struct definition<br />

Function prototypes for:<br />
-ReadDiskImage(char* path)<br />
-ParseMBR(FILE* disk, uint64_t offset)<br />
-ParseFBoot(FILE* disk, uint64_t offset)<br />
-ParseFTable(FILE* path, uint64_t offset)<br />

### The commands.c file contains the implementation of command functions. 
-The InputLoop(FILE* disk) function reads user input from the command line and executes the appropriate command. <br />
The function calls other functions such as PrintHelp(), ls(), cd(char* path), cat(char* path), and stats() depending on the user input.<br />
-The ls() function prints the contents of the current directory.<br />
-The cat(char* path) function reads a file from the disk and prints its contents.<br />

### The readable.c file contains the implementation of read functions. 
-The HumanSize(uint64_t size) function takes a size in bytes and returns a human-readable string representation of the size in bytes, kilobytes, megabytes, or gigabytes.<br />
-The FileAttributes(uint8_t byte) function takes a byte representing file attributes and returns a string representation of the attributes.<br />
-The PartitionType(uint8_t type) function takes a byte representing partition type and returns a string representation of the partition type.<br />

### The reader.c file contains the implementation of read functions. 

### The runtime.c file contains the implementation of runtime functions. 

### The Makefile is used for compiling and linking the project.

## Compiling and running

To compile and run the project on Linux or macOS:
-Open a terminal window.
-Navigate to the directory where your file manager is located.
-Compile your file manager by running “make”.
-Run your file manager by running “./file-manager-c”.
