#ifndef WRITABLE_H
#define WRITABLE_H

# include "src/Identifiable.h"

typedef struct {
	Identifiable identifiable;
	HV* attributes;
	AV* meta;
	char * tag;
	char * xml_id;
	char * url;
	int is_identifiable;
	int is_suppress_ns;
} Writable;

void initialize_writable(Writable* self);

#endif
