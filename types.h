#ifndef TYPES_H
#define TYPES_H

int idpool = 1;

typedef struct {
     int id;
} Identifiable;

typedef struct Node {
	Identifiable identifiable;
	double branch_length;
	SV* parent;
	SV* first_daughter;
	SV* next_sister;
} Node;

#endif