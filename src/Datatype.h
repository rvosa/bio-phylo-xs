#ifndef DATATYPE_H
#define DATATYPE_H

# include "src/Writable.h"

typedef struct {
	Writable * writable;
	char missing;
	char gap;
	AV* meta;
} Datatype;

void initialize_datatype(Datatype* self);
void destroy_datatype(Datatype* self);

#endif
