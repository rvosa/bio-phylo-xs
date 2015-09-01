#ifndef LISTABLE_H
#define LISTABLE_H

#define LISTABLE_INITIAL_SIZE 10

void insert_at_index(SV* obj, SV* element, int index);
void insert(SV* obj, SV* element);
AV* get_entities(SV* obj);
void splice_at_index(SV* obj, SV* element, int index);
void initialize_listable(SV* self);

typedef struct {
	Identifiable identifiable;
    SV **entities;
    int index;
    size_t used;
    size_t size;
} Listable;

#endif
