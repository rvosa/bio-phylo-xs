# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Node.h"
# include "src/Tree.h"

SV* create(const char * classname) {
	Tree * tree;
	Newx(tree, 1, Tree);
	SV* self = sv_setref_pv(newSViv(0), classname, (void *)tree);	
	initialize_tree(self);
	return self;
}

void initialize_tree(SV* self){
	initialize_listable(self);
	Tree* tree = (Tree*)SvIV(SvRV(self));
	tree->is_unrooted = 0;
	tree->is_default = 0;
	((Identifiable*)tree)->_type = _TREE_;
	((Identifiable*)tree)->_container = _FOREST_;
	((Identifiable*)tree)->_size = sizeof(Tree);	
	
}

SV* set_as_unrooted(SV* self){
	Tree* tree = (Tree*)SvIV(SvRV(self));
	tree->is_unrooted = 1;
	return self;
}

SV* set_as_default(SV* self) {
	Tree* tree = (Tree*)SvIV(SvRV(self));
	tree->is_default = 1;
	return self;
}

SV* set_not_default(SV* self) {
	Tree* tree = (Tree*)SvIV(SvRV(self));
	tree->is_default = 0;
	return self;
}

int is_default(SV* self) {
	Tree* tree = (Tree*)SvIV(SvRV(self));
	return tree->is_default;
}

SV* get_root(SV* self) {
	Listable* list = (Listable*)SvIV(SvRV(self));
	int i;
	for ( i = 0; i < list->used; i++ ) {
		Node* node = (Node*)SvIV(SvRV(list->entities[i]));
		if ( node->parent == NULL ) {
			SV* root = list->entities[i];
			SvREFCNT_inc(root);
			return root;
		}
	}
	return NULL;
}