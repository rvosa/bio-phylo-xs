# include "src/TypeSafeData.h"
# include "src/Listable.h"
# include "src/Datatype.h"
# include "src/types.h"

TypeSafeData* create(const char * classname) {
	TypeSafeData *self;
	Newx(self,1,TypeSafeData);
	initialize_typesafedata(self);
	return self;
}

void initialize_typesafedata(TypeSafeData* self){
	initialize_listable((Listable*)self);

	// create datatype object
	Newx(self->datatype,1,Datatype);
	initialize_datatype(self->datatype);
}

Datatype* get_type_object(TypeSafeData* self) {
	return self->datatype;
}

TypeSafeData* set_type_object(TypeSafeData* self, Datatype* type) {
	self->datatype = type;
	return self;
}

void destroy_typesafedata(TypeSafeData* self) {
	destroy_listable((Listable*)self);	
	Safefree(self->datatype);
}