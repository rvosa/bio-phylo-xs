#include "src/TaxaMediator.h"
# include "src/types.h"

TaxaMediator* create(const char* classname) {
	static TaxaMediator* singleton = NULL;
	if ( singleton == NULL ) {
		Newx(singleton,1,TaxaMediator);	
		initialize_taxamediator(singleton);	
	}
	return singleton;
}

void initialize_taxamediator(TaxaMediator* self) {
	self->object = newHV();
	self->id_by_type = newHV();
	self->one_to_one = newHV();
	self->one_to_many = newHV();
	((Identifiable*)self)->_type = _NONE_;
	((Identifiable*)self)->_container = _NONE_;
	((Identifiable*)self)->_index = _TAXAMEDIATOR_IDX_;		
}

//TaxaMediator* register_object( TaxaMediator* self, Identifiable* object );
//TaxaMediator* unregister_object( TaxaMediator* self, Identifiable* object );
//TaxaMediator* set_link( TaxaMediator* self, ... );
//TaxaMediator* get_link( TaxaMediator* self, ... );
//TaxaMediator* remove_link( TaxaMediator* self, ... );
