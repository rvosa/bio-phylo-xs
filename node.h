#ifndef NODE_H
#define NODE_H

# include "listable.h"

typedef struct {
	Listable listable;
	double branch_length;
	SV* parent;
	char * rank;
	SV* tree;
} Node;

#endif