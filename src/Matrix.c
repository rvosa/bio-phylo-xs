# include "src/Matrix.h"
# include "src/TypeSafeData.h"
# include "src/Characters.h"
# include "src/types.h"

Matrix* create(const char * classname) {
	Matrix *self;
	Newx(self,1,Matrix);
	((Identifiable*)self)->_class = savepv(classname);
	((Writable*)self)->tag = savepv("characters");
	initialize_matrix(self);
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
	((Identifiable*)chars)->_class = savepv("Bio::Phylo::Matrices::Characters");
	((Writable*)chars)->tag = savepv("chars");		
	initialize_characters(chars);
	self->characters = chars;
}