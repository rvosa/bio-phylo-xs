# include "src/types.h"
# include "src/Identifiable.h"

void initialize_identifiable(Identifiable* self){
	self->id = idpool++;
}

int get_id(Identifiable* self){
	return self->id;
}

int _type(Identifiable* self){
	return self->_type;
}

int _container(Identifiable* self){
	return self->_container;
}

size_t _size(Identifiable* self){
	return self->_size;
}

SV* sv(Identifiable* self) {
	return self->sv;
}

SV* ref(Identifiable* self) {
	return self->ref;
}

int refcnt (Identifiable* self) {
	return SvREFCNT(self->sv);
}

void destroy_identifiable(Identifiable* self) {
	// as of now, there is actually nothing to clean up here:
	// the SV* member is cleaned up by perl (I hope)
}