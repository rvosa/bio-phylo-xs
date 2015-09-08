#ifndef DATATYPE_H
#define DATATYPE_H

# include "src/Writable.h"

typedef struct {
	Writable * writable;
	char missing;
	char gap;
	AV* meta;
} Datatype;

initialize_datatype(Datatype* self);

#endif
