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

int _index(Identifiable* self) {
	return self->_index;
}

void destroy_identifiable(Identifiable* self) {
	//Safefree(self);
}