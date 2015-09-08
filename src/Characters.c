# include "src/Characters.h"
# include "src/TypeSafeData.h"

Characters* create(const char * classname) {
	Characters *self;
	Newx(self,1,Characters);
	((Identifiable*)self)->_class = savepv(classname);
	((Writable*)self)->tag = savepv("chars");		
	initialize_characters(self);
	return self;
}

void initialize_characters(Characters* self){
	initialize_typesafedata((TypeSafeData*)self);
	((Identifiable*)self)->_type = _CHARACTERS_;	
	((Identifiable*)self)->_container = _NONE_;		
}