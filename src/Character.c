# include "src/Character.h"
# include "src/TypeSafeData.h"

Character* create(const char * classname) {
	Character *self;
	Newx(self,1,Character);
	((Identifiable*)self)->_class = savepv(classname);
	((Writable*)self)->tag = savepv("char");	
	initialize_character(self);
	return self;
}

void initialize_character(Character* self){
	initialize_typesafedata((TypeSafeData*)self);
	((Identifiable*)self)->_type = _CHARACTER_;	
	((Identifiable*)self)->_container = _CHARACTERS_;			
}