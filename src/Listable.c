# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"

void initialize_listable(Listable* self){
	initialize_identifiable((Identifiable*)self);
	self->index = 0;
	self->size  = LISTABLE_INITIAL_SIZE;
	self->used  = 0;
	self->entities = malloc(sizeof(Identifiable *) * LISTABLE_INITIAL_SIZE);
}

int can_contain(Listable* self, Identifiable* element) {
	Identifiable* listid = (Identifiable*)self;
	
	// in most cases, a simple comparison between the _type
	// and _container fields should suffice
	if ( listid->_type == element->_container ) {
		return 1;
	}
	
	// tree nodes can go into trees, but also in other nodes
	// as their children
	else if ( listid->_type == _NODE_ && element->_type == _NODE_ ) {
		return 1;
	}
	
	// XXX once we deal with raw character data going into matrix rows
	// we will need one more possibility here
	else {
		return 0;
	}
}

void insert(Listable* self, Identifiable* element) {
	if ( can_contain(self,element) ) {
	
		// resize if needed
		if ( self->used == self->size ) {
			self->size = ( self->size * 3 ) / 2 + 8;
			self->entities = (Identifiable **) realloc(self->entities, self->size * sizeof(Identifiable*));
		}
		self->entities[self->used++] = element;
		SvREFCNT_inc(element->ref);
	}
	else {
		croak("Object mismatch!");
	}
}

void insert_at_index(Listable* self, Identifiable* element, int index) {		
	if ( can_contain(self,element) ) {
	
		// resize if needed
		if ( index > ( self->size - 1 ) ) {
			self->size = index + 1;
			self->entities = (Identifiable **) realloc(self->entities, self->size * sizeof(Identifiable*));
		}
		
		if ( index >= self->used ) {
			self->used = index + 1;
		}
		
		self->entities[index] = element;
		SvREFCNT_inc(element->ref);
	}
	else {
		croak("Object mismatch!");
	}
}

void splice_at_index(Listable* self, Identifiable* element, int index) {
	if ( can_contain(self,element) ) {
	
		// resize if needed
		if ( ( self->used + 1 ) == self->size ) {
			self->size = ( self->size * 3 ) / 2 + 8;
			self->entities = (Identifiable **) realloc(self->entities, self->size * sizeof(Identifiable*));
		}
		
		// move any subsequent elements over
		int i;
		for ( i = ( self->used - 1 ); i >= index; i-- ) {
			self->entities[i+1] = self->entities[i];
		}
		self->entities[index] = element;
		SvREFCNT_inc(element->ref);
	}
	else {
		croak("Object mismatch!");
	}
}

AV* get_entities(Listable* self) {
	AV* ret = newAV();
	int i;
	for ( i = 0; i < self->used; i++ ) {
		av_push(ret, self->entities[i]->sv);
	}
	return ret;
}

void destroy_listable(Listable* self) {
	destroy_identifiable((Identifiable*)self);
	int i;
	for ( i = 0; i < self->used; i++ ) {	
		SvREFCNT_dec(self->entities[i]->ref);
	}
	Safefree(self->entities);	
}