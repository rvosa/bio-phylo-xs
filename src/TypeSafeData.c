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
	self->meta = newAV();
	
	// maybe something HAS to go here?
	((Identifiable*)self)->_container = _NONE_;
	((Identifiable*)self)->_type = _NONE_;	

	// create datatype object
	Datatype* datatype;
	Newx(datatype,1,Datatype);
	((Identifiable*)datatype)->_class = savepv("Bio::PhyloXS::Matrices::Datatype");
	((Writable*)datatype)->tag = savepv("states");	
	initialize_datatype(datatype);
	self->datatype = datatype;
}

void destroy_typesafedata(TypeSafeData* self) {
	//destroy_datatype(self->datatype);
	destroy_listable((Listable*)self);
}