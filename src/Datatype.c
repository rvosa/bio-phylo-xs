# include "src/Datatype.h"
# include "src/Writable.h"

Datatype* create(const char * classname) {
	Datatype *self;
	Newx(self,1,Datatype);
	((Identifiable*)self)->_class = savepv(classname);
	((Writable*)self)->tag = savepv("states");
	initialize_datatype(self);
	return self;
}

void initialize_datatype(Datatype* self){
	initialize_writable((Writable*)self);
	self->missing = '?';
	self->gap = '-';
	self->meta = newAV();
	((Identifiable*)self)->_type = _DATATYPE_;
}