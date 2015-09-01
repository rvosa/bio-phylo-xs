#ifndef NODE_H
#define NODE_H

# include "src/listable.h"

void initialize_node(SV* self);

typedef struct {
	Listable listable;
	double branch_length;
	SV* parent;
	char * rank;
	SV* tree;
} Node;

#endif