#include "../headers/reader.h"

Reader* Reader_new(FILE* filename)
{
    Reader* self = (Reader*) malloc(sizeof(Reader));
    Reader_init(self, filename);
    return self;
}

void Reader_init(Reader* self, FILE* filename)
{
    self->file = filename;
    self->mbr = MBR_new(filename);
    self->offset += 512;
    for (int i = 0; i < 4; i++) {
        self->partitions[i] = Partition_new(filename, self->offset);
    }
    self->offset = 0;
}

void Reader_print(Reader* self)
{
    MBR_print(self->mbr);
    for (int i = 0; i < 4; i++) {
        Partition_print(self->partitions[i]);
    }
}