# include "src/Datum.h"
# include "src/TypeSafeData.h"
# include "src/types.h"

Datum* create(const char * classname) {
	Datum *self;
	Newx(self,1,Datum);
	((Writable*)self)->tag = savepv("row");
	initialize_datum(self);
	((Identifiable*)self)->_class = savepv(classname);	
	return self;
}

void initialize_datum(Datum* self){
	initialize_typesafedata((TypeSafeData*)self);
	self->position = 0;
	self->weight = 1.0;
	self->annotations = newAV();
	((Identifiable*)self)->_type = _DATUM_;
	((Identifiable*)self)->_container = _MATRIX_;
}

void destroy_datum(Datum* self) {
	destroy_typesafedata((TypeSafeData*)self);
}