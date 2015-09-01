# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Node.h"

SV* create(const char * classname) {
	Node* node;
	Newx(node, 1, Node);
	SV* self = sv_setref_pv(newSViv(0), classname, (void *)node);
	initialize_node(self);
	return self;
}

SV* _to_sv(Node* node) {
	SV* self = newSViv((IV)node);
  	SV* obj_ref = newRV_noinc(self);
  	sv_bless(obj_ref, gv_stashpv("Bio::PhyloXS::Forest::Node", TRUE));
	SvREADONLY_on(self);
	return obj_ref;
}

Node* _to_node(SV* self) {
	return (Node*)SvIV(SvRV(self));
}

void initialize_node(SV* self) {
	initialize_listable(self);
	Node* node = _to_node(self);
	node->parent = NULL;
	node->rank = NULL;
	node->tree = NULL;
	node->branch_length = 0.0;
	((Identifiable*)node)->_type = _NODE_;
	((Identifiable*)node)->_container = _TREE_;
	((Identifiable*)node)->_size = sizeof(Node);	
}

double get_branch_length(SV* self) {
	return _to_node(self)->branch_length;
}

void set_branch_length(SV* self, double length) {
	_to_node(self)->branch_length = length;
}

AV* get_children(SV* self) {
	return get_entities(self);
}

AV* get_ancestors(SV* self) {
	AV* ret = newAV();
	Node* parent = _to_node(self)->parent;
	while(parent != NULL) {
		SV* svp = _to_sv(parent);
		av_push(ret, svp);
		parent = parent->parent;
	}
	return ret;
}

void _desc(SV* parent, AV* set);

void _desc(SV* parent, AV* set) {
	Listable* pl = (Listable*)SvIV(SvRV(parent));
	int i;
	for ( i = 0; i < pl->used; i++ ) {
		SV* child = pl->entities[i];
		av_push(set, child);
		_desc(child, set);
	}	
}

SV* get_first_daughter(SV* self) {
	Listable* pl = (Listable*)SvIV(SvRV(self));
	if ( pl->used > 0 ) {
		return pl->entities[0];
	}
	else {
		return NULL;
	}
}

int is_terminal(SV* self) {
	return ((Listable*)SvIV(SvRV(self)))->used == 0;
}

AV* get_descendants(SV* self) {
	AV* ret = newAV();	
	_desc(self, ret);
	return ret;	
}

void _ido(SV* parent, int *tf, int id);

void _ido(SV* parent, int *tf, int id) {
	Listable* pl = (Listable*)SvIV(SvRV(parent));
	int i;
	for ( i = 0; i < pl->used; i++ ) {
		SV* child = pl->entities[i];
		if ( ((Identifiable*)SvIV(SvRV(child)))->id == id ) {
			*tf = 1;
			break;
		}
		_ido(child, tf, id);
	}	
}

// tests if invocant is descendant of argument
int is_descendant_of(SV* self, SV* other) {
	int id = ((Identifiable*)SvIV(SvRV(self)))->id;
	int ret = 0;
	_ido(other,&ret,id);
	return ret;
}

void set_raw_parent(SV* self, SV* parent) {
	_to_node(self)->parent = parent;
	SvREFCNT_inc(parent);
}

SV* get_parent(SV* self) {
	return _to_node(self)->parent;
}

void set_raw_child(SV* self, SV* child, ...) {	
	Inline_Stack_Vars;	// handle variable argument list
	
	// determine where to place the child, 
	// default -1 means at the end 
	signed int position = -1;
	if ( Inline_Stack_Items > 2 ) {
		position = SvIV(Inline_Stack_Item(2));
	}
	
	if ( position == -1 ) {
		insert(self, child);
	}
	else {
		insert_at_index(self,child,position);
	}

	Inline_Stack_Void; // handle variable argument list
}

char* get_rank(SV* self) {
	return _to_node(self)->rank;
}

void set_rank(SV* obj, char * rank) {
	_to_node(obj)->rank = savepv(rank);
}

SV* get_tree(SV* obj) {
	return _to_node(obj)->tree;
}

void set_tree(SV* obj, SV* tree) {
	_to_node(obj)->tree = tree;
	SvREFCNT_inc(tree);
}