# include "types.h"
# include "identifiable.h"

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