# include "src/Datatype.h"
# include "src/Writable.h"
# include "src/types.h"

Datatype* create(const char * classname) {
	Datatype *self;
	Newx(self,1,Datatype);
	((Writable*)self)->tag = savepv("states");
	initialize_datatype(self);
	((Identifiable*)self)->_class = savepv(classname);	
	return self;
}

void initialize_datatype(Datatype* self){
	initialize_writable((Writable*)self);
	self->missing = '?';
	self->gap = '-';
	self->meta = newAV();
	((Identifiable*)self)->_type = _DATATYPE_;
	((Identifiable*)self)->_container = _NONE_;		
}

void destroy_datatype(Datatype* self) {
	destroy_writable((Writable*)self);
}