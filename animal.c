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
	Animal * animal;
	SV      * obj;
	SV      * obj_ref;
	Newx(animal, 1, Animal);
	obj = newSViv((IV)animal);
	obj_ref = newRV_noinc(obj);
	sv_bless(obj_ref, gv_stashpv(classname, GV_ADD));
	SvREADONLY_on(obj);
	return obj_ref;
}

char* get_name(SV* obj) {
	return ((Animal*)SvIV(SvRV(obj)))->name;
}

void set_name(SV* obj, const char * name) {
	Animal* animal = (Animal*)SvIV(SvRV(obj));
	animal->name = savepv(name);
}

int get_legs(SV* obj) {
	return ((Animal*)SvIV(SvRV(obj)))->legs;
}

void set_legs(SV* obj, int legs) {
	Animal* animal = (Animal*)SvIV(SvRV(obj));
	animal->legs = legs;
}