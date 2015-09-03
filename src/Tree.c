# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Node.h"
# include "src/Tree.h"

Tree* create(const char * classname) {
    Tree *self;

    /* allocate and initialize struct */
    Newx(self, 1, Tree);
    initialize_tree(self);

    /* create perl object and ref; store pointer to object in struct */
    SV* perlref = newSViv((IV)self);
    SV* obj_ref = newRV_noinc(perlref);
    sv_bless(obj_ref, gv_stashpv(classname, TRUE));
    SvREADONLY_on(perlref);
    ((Identifiable*)self)->sv = obj_ref;

    return self;	
}

void initialize_tree(Tree* self){
	initialize_listable((Listable*)self);
	self->is_unrooted = 0;
	self->is_default = 0;
	((Identifiable*)self)->_type = _TREE_;
	((Identifiable*)self)->_container = _FOREST_;
	((Identifiable*)self)->_size = sizeof(Tree);	
}

Tree* set_as_unrooted(Tree* self){
	self->is_unrooted = 1;
	return self;
}

Tree* set_as_default(Tree* self) {
	self->is_default = 1;
	return self;
}

Tree* set_not_default(Tree* self) {
	self->is_default = 0;
	return self;
}

int is_default(Tree* self) {
	return self->is_default;
}

Node* get_root(Tree* self) {
	Listable* list = (Listable*)self;
	int i;
	for ( i = 0; i < list->used; i++ ) {
		Node* node = (Node*)list->entities[i];
		if ( node->parent == NULL ) {			
			SvREFCNT_inc(((Identifiable*)node)->sv);
			return node;
		}
	}
	return NULL;
}

void destroy_tree(Tree* self) {
	destroy_listable((Listable*)self);
	Safefree(self);
}