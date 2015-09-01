# include "src/types.h"
# include "src/identifiable.h"

SV* create(const char * classname) {
	Identifiable * identifiable;
	Newx(identifiable, 1, Identifiable);
	SV* self = sv_setref_pv(newSViv(0), classname, (void *)identifiable);	
	initialize_identifiable(self);
}

void initialize_identifiable(SV* self){
	Identifiable* identifiable = (Identifiable*)SvIV(SvRV(self));
	identifiable->id = idpool++;
}

int get_id(SV* self){
	return ((Identifiable*)SvIV(SvRV(self)))->id;
}

int _type(SV* self){
	return ((Identifiable*)SvIV(SvRV(self)))->_type;
}

int _container(SV* self){
	return ((Identifiable*)SvIV(SvRV(self)))->_container;
}

size_t _size(SV* self){
	return ((Identifiable*)SvIV(SvRV(self)))->_size;
}