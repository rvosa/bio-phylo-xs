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

int get_id(SV* obj){
	return ((Identifiable*)SvIV(SvRV(obj)))->id;
}

int _type(SV* obj){
	return ((Identifiable*)SvIV(SvRV(obj)))->_type;
}

void identify(SV* obj){
	Identifiable* identifiable = (Identifiable*)SvIV(SvRV(obj));
	identifiable->id = idpool++;
}