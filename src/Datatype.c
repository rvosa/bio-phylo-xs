# include "src/Datatype.h"
# include "src/Writable.h"
# include "src/types.h"

Datatype* create(const char * classname) {
	Datatype *self;
	Newx(self,1,Datatype);	
	initialize_datatype(self);
	return self;
}

void initialize_datatype(Datatype* self){
	initialize_writable((Writable*)self);
	self->missing = '?';
	self->gap = '-';
	((Identifiable*)self)->_type = _DATATYPE_;
	((Identifiable*)self)->_container = _NONE_;
	((Identifiable*)self)->_index = _DATATYPE_IDX_;	
}

char get_missing(Datatype* self) {
	return self->missing;
}

Datatype* set_missing(Datatype* self, char missing) {
	self->missing = missing;
	return self;
}

char get_gap(Datatype* self) {
	return self->gap;
}

Datatype* set_gap(Datatype* self, char gap) {
	self->gap = gap;
	return self;
}

void destroy_datatype(Datatype* self) {
	destroy_writable((Writable*)self);
	//Safefree(self);
}