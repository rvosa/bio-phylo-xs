# include "src/Character.h"
# include "src/TypeSafeData.h"
# include "src/types.h"

Character* create(const char * classname) {
	Character *self;
	Newx(self,1,Character);
	((Writable*)self)->tag = savepv("char");
	initialize_character(self);
	((Identifiable*)self)->_class = savepv(classname);	
	return self;
}

void initialize_character(Character* self){
	initialize_typesafedata((TypeSafeData*)self);
	((Identifiable*)self)->_type = _CHARACTER_;
	((Identifiable*)self)->_container = _CHARACTERS_;
}

void destroy_character(Character* self){
	destroy_typesafedata((TypeSafeData*)self);
}