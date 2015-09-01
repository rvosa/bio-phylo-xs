# include "types.h"
# include "identifiable.h"
# include "listable.h"

SV* create(const char * classname) {
	Listable * listable;
	Newx(listable, 1, Listable);
	SV* self = sv_setref_pv(newSViv(0), classname, (void *)listable);	
	initialize_listable(self);
	return self;
}

void initialize_listable(SV* self){
	initialize_identifiable(self);
	Listable* listable = (Listable*)SvIV(SvRV(self));
	listable->index = 0;
	listable->size  = LISTABLE_INITIAL_SIZE;
	listable->used  = 0;
	listable->entities = malloc(sizeof(SV *) * LISTABLE_INITIAL_SIZE);
}

int can_contain(SV* self, SV* element) {

	Identifiable* listid = (Identifiable*)SvIV(SvRV(self));
	Identifiable* eltid = (Identifiable*)SvIV(SvRV(element));
	
	// in most cases, a simple comparison between the _type
	// and _container fields should suffice
	if ( listid->_type == eltid->_container ) {
		return 1;
	}
	
	// tree nodes can go into trees, but also in other nodes
	// as their children
	else if ( listid->_type == _NODE_ && eltid->_type == _NODE_ ) {
		return 1;
	}
	
	// XXX once we deal with raw character data going into matrix rows
	// we will need one more possibility here
	else {
		return 0;
	}
}

void insert(SV* self, SV* element) {
	if ( can_contain(self,element) ) {
		Listable* list = (Listable*)SvIV(SvRV(self));
	
		// resize if needed
		if ( list->used == list->size ) {
			list->size = ( list->size * 3 ) / 2 + 8;
			list->entities = (SV **) realloc(list->entities, list->size * sizeof(SV*));
		}
		list->entities[list->used++] = element;
		SvREFCNT_inc(element);
	}
	else {
		croak("Object mismatch!");
	}
}

void insert_at_index(SV* self, SV* element, int index) {		
	if ( can_contain(self,element) ) {
		Listable* list = (Listable*)SvIV(SvRV(self));
	
		// resize if needed
		if ( index > ( list->size - 1 ) ) {
			list->size = index + 1;
			list->entities = (SV **) realloc(list->entities, list->size * sizeof(SV*));
		}
		list->entities[index] = element;
		SvREFCNT_inc(element);
	}
	else {
		croak("Object mismatch!");
	}
}

void splice_at_index(SV* self, SV* element, int index) {
	if ( can_contain(self,element) ) {
		Listable* list = (Listable*)SvIV(SvRV(self));
	
		// resize if needed
		if ( ( list->used + 1 ) == list->size ) {
			list->size = ( list->size * 3 ) / 2 + 8;
			list->entities = (SV **) realloc(list->entities, list->size * sizeof(SV*));
		}
		
		// move any subsequent elements over
		int i;
		for ( i = ( list->used - 1 ); i >= index; i-- ) {
			list->entities[i+1] = list->entities[i];
		}
		list->entities[index] = element;
		SvREFCNT_inc(element);
	}
	else {
		croak("Object mismatch!");
	}
}

AV* get_entities(SV* self) {
	Listable* list = (Listable*)SvIV(SvRV(self));
	AV* ret = newAV();
	int i;
	for ( i = 0; i < list->used; i++ ) {
		av_push(ret, list->entities[i]);
	}
	return ret;
}