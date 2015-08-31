#ifndef TREE_H
#define TREE_H

# include "listable.h"

typedef struct {
	Listable listable;
	int is_default;
	int is_unrooted;
} Tree;

#endif
