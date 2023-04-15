#include <stdio.h>

#include "Partition.h"
#include "MBR.h"

typedef struct Reader
{
    int offset;
    FILE* file;
    MBR* mbr;
    Partition* partitions[4];
} Reader;

Reader* Reader_new(FILE* filename);
void Reader_init(Reader* self, FILE* filename);
void Reader_print(Reader* self);
void Reader_destroy(Reader* self);
