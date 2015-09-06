# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Node.h"
# include "src/Tree.h"

Tree* create(const char * classname) {
    Tree *self;
    Newx(self,1,Tree);
    ((Identifiable*)self)->_class = savepv(classname);
    initialize_tree(self);
    return self;
}

void initialize_tree(Tree* self){
	initialize_listable((Listable*)self);
	self->is_unrooted = 0;
	self->is_default = 0;
	((Identifiable*)self)->_type = _TREE_;
	((Identifiable*)self)->_container = _FOREST_;
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
	SSize_t max = av_len(list->entities);
	int i;
	for ( i = 0; i <= max; i++ ) {
		if ( av_exists(list->entities,i) ) {
			SV* sv = *(av_fetch(list->entities, i, 0));
			Node* node = (Node*)SvIV(SvRV(sv));
			if ( node->parent == NULL ) {
				return node;
			}
		}
	}
	return NULL;
}

void destroy_tree(Tree* self) {
	destroy_listable((Listable*)self);
	//Safefree(self);
}