#ifndef TREE_H
#define TREE_H

# include "src/listable.h"

void initialize_tree(SV* self);

typedef struct {
	Listable listable;
	int is_default;
	int is_unrooted;
} Tree;

#endif
