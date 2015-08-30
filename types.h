#ifndef TYPES_H
#define TYPES_H

// gets incremented for each object
int idpool = 1;

// Bio::Phylo object type constants
#define _NONE_ 1
#define _NODE_ 2
#define _TREE_ 3
#define _FOREST_ 4
#define _TAXON_ 5
#define _TAXA_ 6
#define _DATUM_ 7
#define _MATRIX_ 8
#define _MATRICES_ 9
#define _SEQUENCE_ 10
#define _ALIGNMENT_ 11
#define _CHAR_ 12
#define _PROJECT_ 9
#define _CHARSTATE_ 13
#define _CHARSTATESEQ_ 14
#define _MATRIXROW_ 15
#define _ANNOTATION_ 16
#define _DICTIONARY_ 17
#define _DOMCREATOR_ 18
#define _META_ 19
#define _DESCRIPTION_ 20
#define _RESOURCE_ 21
#define _DOCUMENT_ 22
#define _ELEMENT_ 23
#define _CHARACTERS_ 24
#define _CHARACTER_ 25
#define _SET_ 26
#define _MODEL_ 27
#define _OPERATION_ 28
#define _DATATYPE_ 29

typedef struct {
    int id; // from idpool
    int _type; // from defines
    int _container; // from defines
    size_t _size; // set by child class
} Identifiable;

// the general idea is that we can
// have inheritance and extension
// by having the "superclass" struct
// be the first member of the child struct
typedef struct Node {
	Identifiable identifiable;
	double branch_length;
	SV* parent;
	SV* first_daughter;
	SV* next_sister;
} Node;

#endif
