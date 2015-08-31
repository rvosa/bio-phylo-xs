#ifndef NODE_H
#define NODE_H

typedef struct Node {
	Identifiable identifiable;
	double branch_length;
	struct Node* parent;
	struct Node* first_daughter;
	struct Node* next_sister;
} Node;

#endif