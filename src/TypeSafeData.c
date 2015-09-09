# include "src/TypeSafeData.h"
# include "src/Listable.h"
# include "src/Datatype.h"
# include "src/types.h"

TypeSafeData* create(const char * classname) {
	TypeSafeData *self;
	Newx(self,1,TypeSafeData);
	((Writable*)self)->tag = savepv("tsd");	
	initialize_typesafedata(self);
	((Identifiable*)self)->_class = savepv(classname);	
	return self;
}

void initialize_typesafedata(TypeSafeData* self){
	initialize_listable((Listable*)self);
	
	// maybe something HAS to go here?
	((Identifiable*)self)->_container = _NONE_;
	((Identifiable*)self)->_type = _NONE_;	

	// create datatype object
	Newx(self->datatype,1,Datatype);
	((Identifiable*)self->datatype)->_class = savepv("Bio::PhyloXS::Matrices::Datatype");
	((Writable*)self->datatype)->tag = savepv("states");	
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
}