# include "types.h"
# include "identifiable.h"
# include "listable.h"

SV* create(const char * classname) {
	Listable * listable;
	Newx(listable, 1, Listable);
	return sv_setref_pv(newSViv(0), classname, (void *)listable);	
}

void initialize(SV* obj){
	Listable* listable = (Listable*)SvIV(SvRV(obj));
	listable->index = 0;
	listable->size  = 1;
	listable->used  = 0;
	listable->entities = malloc(sizeof(SV *));
}

int can_contain(SV* obj, SV* element) {

	Identifiable* listid = (Identifiable*)SvIV(SvRV(obj));
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

void insert(SV* obj, SV* element) {
	if ( can_contain(obj,element) ) {
		Listable* list = (Listable*)SvIV(SvRV(obj));
	
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

void insert_at_index(SV* obj, SV* element, int index) {		
	if ( can_contain(obj,element) ) {
		Listable* list = (Listable*)SvIV(SvRV(obj));
	
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

void splice_at_index(SV* obj, SV* element, int index) {
	if ( can_contain(obj,element) ) {
		Listable* list = (Listable*)SvIV(SvRV(obj));
	
		// resize if needed
		if ( ( list->used + 1 ) == list->size ) {
			list->size = ( list->size * 3 ) / 2 + 8;
			list->entities = (SV **) realloc(list->entities, list->size * sizeof(SV*));
		}
		
		// move any subsequent elements over
		for ( int i = ( list->used - 1 ); i >= index; i-- ) {
			list->entities[i+1] = list->entities[i];
		}
		list->entities[index] = element;
		SvREFCNT_inc(element);
	}
	else {
		croak("Object mismatch!");
	}
}

AV* get_entities(SV* obj) {
	Listable* list = (Listable*)SvIV(SvRV(obj));
	AV* ret = newAV();
	for ( int i = 0; i < list->used; i++ ) {
		av_push(ret, list->entities[i]);
	}
	return ret;
}