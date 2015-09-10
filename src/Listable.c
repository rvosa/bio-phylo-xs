# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Writable.h"

void initialize_listable(Listable* self){
	initialize_writable((Writable*)self);
	self->index = 0;
	self->entities = newAV();
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
		SV* sv = newSV(0);
		int idx = element->_index;
		sv_setref_pv( sv, package[idx], (void*)element );
		SvREFCNT_inc(sv);
		av_push(self->entities, sv);		
	}
	else {
		croak("Object mismatch!");
	}
}

void insert_at_index(Listable* self, Identifiable* element, int index) {		
	if ( can_contain(self,element) ) {	
		SV* sv = newSV(0);	
		int idx = element->_index;		
		sv_setref_pv( sv, package[idx], (void*)element );
		SvREFCNT_inc(sv);
		av_store(self->entities, index, sv);
	}
	else {
		croak("Object mismatch!");
	}
}

void splice_at_index(Listable* self, Identifiable* element, int index) {
	if ( can_contain(self,element) ) {
		
		// move any subsequent elements over
		//int i;
		//for ( i = ( self->used - 1 ); i >= index; i-- ) {
		//	self->entities[i+1] = self->entities[i];
		//}
		//self->entities[index] = element;
		//SvREFCNT_inc(element->ref);
	}
	else {
		croak("Object mismatch!");
	}
}

AV* get_entities(Listable* self) {
	return self->entities;
}

void destroy_listable(Listable* self) {
	destroy_identifiable((Identifiable*)self);
	//int i;
	//for ( i = 0; i < self->used; i++ ) {	
	//	SvREFCNT_dec(self->entities[i]->ref);
	//}
}