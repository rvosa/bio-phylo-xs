#ifndef TYPESAFEDATA_H
#define TYPESAFEDATA_H

# include "src/Listable.h"
# include "src/Datatype.h"

typedef struct {
	Listable * listable;
	Datatype * datatype;
	char missing;
	char gap;
	AV* meta;
} TypeSafeData;

initialize_typesafedata(TypeSafeData* self);

#endif
