# include "src/Characters.h"
# include "src/TypeSafeData.h"
# include "src/types.h"

Characters* create(const char * classname) {
	Characters *self;
	Newx(self,1,Characters);		
	initialize_characters(self);
	return self;
}

void initialize_characters(Characters* self){
	initialize_typesafedata((TypeSafeData*)self);
	((Identifiable*)self)->_type = _CHARACTERS_;	
	((Identifiable*)self)->_container = _NONE_;	
	((Identifiable*)self)->_index = _CHARACTERS_IDX_;			
}

void destroy_characters(Characters* self) {
	destroy_typesafedata((TypeSafeData*)self);
}