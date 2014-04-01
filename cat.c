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
	Cat * cat;
	SV  * obj;
	SV  * obj_ref;
	Newx(cat, 1, Cat);
	obj = newSViv((IV)cat);
	obj_ref = newRV_noinc(obj);
	sv_bless(obj_ref, gv_stashpv(classname, GV_ADD));
	SvREADONLY_on(obj);
	return obj_ref;
}

char* get_owner(SV* obj) {
	return ((Cat*)SvIV(SvRV(obj)))->owner;
}

void set_owner(SV* obj, const char * owner) {
	Cat* cat = (Cat*)SvIV(SvRV(obj));
	cat->owner = savepv(owner);
}