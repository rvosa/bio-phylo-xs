# include "src/Matrix.h"
# include "src/TypeSafeData.h"
# include "src/Characters.h"
# include "src/types.h"

Matrix* create(const char * classname) {
	Matrix *self;
	Newx(self,1,Matrix);
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
	((Identifiable*)self)->_container = _MATRIX_IDX_;		
	
	// allocate and initialize Characters* field
	Newx(self->characters,1,Characters);
	initialize_characters(self->characters);
}

void destroy_matrix(Matrix* self) {
	destroy_characters(self->characters);
	destroy_typesafedata((TypeSafeData*)self);
}