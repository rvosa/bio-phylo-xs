#ifndef DATUM_H
#define DATUM_H

# include "src/TypeSafeData.h"

typedef struct {
	TypeSafeData * type;
	int position;
	double weight;
	AV* annotations;
} Datum;

initialize_datum(Datum* self);

#endif
