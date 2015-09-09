# include "src/Matrix.h"
# include "src/TypeSafeData.h"
# include "src/Characters.h"
# include "src/types.h"

Matrix* create(const char * classname) {
	Matrix *self;
	Newx(self,1,Matrix);
	((Writable*)self)->tag = savepv("characters");
	initialize_matrix(self);
	((Identifiable*)self)->_class = savepv(classname);	
	return self;
}

void initialize_matrix(Matrix* self){
	initialize_typesafedata((TypeSafeData*)self);
	self->charlabels = newAV();
	self->statelabels = newAV();
	self->gapmode = 1;
	self->matchchar = '.';
	self->polymorphism = 0;
	self->respectcase = 1;
	((Identifiable*)self)->_type = _MATRIX_;
	((Identifiable*)self)->_container = _MATRICES_;	
	
	// create Characters *
	Characters *chars;
	Newx(chars,1,Characters);
	((Identifiable*)chars)->_class = savepv("Bio::PhyloXS::Matrices::Characters");
	((Writable*)chars)->tag = savepv("chars");		
	initialize_characters(chars);
	self->characters = chars;
}

void destroy_matrix(Matrix* self) {
	destroy_characters(self->characters);
	destroy_typesafedata((TypeSafeData*)self);
}