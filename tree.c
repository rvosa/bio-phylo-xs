# include "types.h"
# include "identifiable.h"
# include "listable.h"
# include "node.h"
# include "tree.h"

SV* create(const char * classname) {
	Tree * tree;
	Newx(tree, 1, Tree);
	return sv_setref_pv(newSViv(0), classname, (void *)tree);	
}

void initialize(SV* obj){
	Tree* tree = (Tree*)SvIV(SvRV(obj));
	tree->is_unrooted = 0;
	tree->is_default = 0;
	((Identifiable*)tree)->_type = _TREE_;
	((Identifiable*)tree)->_container = _FOREST_;
	((Identifiable*)tree)->_size = sizeof(Tree);	
	
}

SV* set_as_unrooted(SV* obj){
	Tree* tree = (Tree*)SvIV(SvRV(obj));
	tree->is_unrooted = 1;
	return obj;
}

SV* set_as_default(SV* obj) {
	Tree* tree = (Tree*)SvIV(SvRV(obj));
	tree->is_default = 1;
	return obj;
}

SV* set_not_default(SV* obj) {
	Tree* tree = (Tree*)SvIV(SvRV(obj));
	tree->is_default = 0;
	return obj;
}

int is_default(SV* obj) {
	Tree* tree = (Tree*)SvIV(SvRV(obj));
	return tree->is_default;
}

SV* get_root(SV* obj) {
	Listable* list = (Listable*)SvIV(SvRV(obj));
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