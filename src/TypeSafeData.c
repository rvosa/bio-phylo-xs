# include "src/TypeSafeData.h"
# include "src/Listable.h"
# include "src/Datatype.h"

TypeSafeData* create(const char * classname) {
	TypeSafeData *self;
	Newx(self,1,TypeSafeData);
	((Identifiable*)self)->_class = savepv(classname);
	initialize_typesafedata(self);
	return self;
}

void initialize_typesafedata(TypeSafeData* self){
	initialize_listable((Listable*)self);
	self->meta = newAV();

	// create datatype object
	Datatype* datatype;
	Newx(datatype,1,Datatype);
	((Identifiable*)datatype)->_class = savepv("Bio::PhyloXS::Matrices::Datatype");
	initialize_datatype(datatype);
	self->datatype = datatype;
}