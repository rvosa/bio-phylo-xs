/*
Allocate memory with Newx if it's
available - if it's an older perl
that doesn't have Newx then we
resort to using New.
*/
#ifndef Newx
#  define Newx(v,n,t) New(0,v,n,t)
#endif
    
# include "types.h"

SV* create(const char * classname) {
	Identifiable * identifiable;
	Newx(identifiable, 1, Identifiable);
	return sv_setref_pv(newSViv(0), classname, (void *)identifiable);	
}

void initialize(SV* obj){
	Identifiable* identifiable = (Identifiable*)SvIV(SvRV(obj));
	identifiable->id = idpool++;
}

int get_id(SV* obj){
	return ((Identifiable*)SvIV(SvRV(obj)))->id;
}

int _type(SV* obj){
	return ((Identifiable*)SvIV(SvRV(obj)))->_type;
}

int _container(SV* obj){
	return ((Identifiable*)SvIV(SvRV(obj)))->_container;
}

size_t _size(SV* obj){
	return ((Identifiable*)SvIV(SvRV(obj)))->_size;
}