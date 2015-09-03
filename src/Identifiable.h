#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

// gets incremented for each object
int idpool = 1;

typedef struct {
    int id; // from idpool
    int _type; // from defines
    int _container; // from defines
    size_t _size; // set by child class
    SV* sv; // reference to perl struct
    SV* ref;
} Identifiable;

void initialize_identifiable(Identifiable* self);
void destroy_identifiable(Identifiable* self);

#endif
