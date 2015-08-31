# include "types.h"
# include "identifiable.h"
# include "listable.h"
# include "node.h"

SV* create(const char * classname) {
	Node* node;
	Newx(node, 1, Node);
	return sv_setref_pv(newSViv(0), classname, (void *)node);	
}

SV* _to_sv(Node* node) {
	SV* obj = newSViv((IV)node);
  	SV* obj_ref = newRV_noinc(obj);
  	sv_bless(obj_ref, gv_stashpv("Node", TRUE));
	SvREADONLY_on(obj);
	return obj_ref;
}

Node* _to_node(SV* obj) {
	return (Node*)SvIV(SvRV(obj));
}

void initialize(SV* obj) {
	Node* node = _to_node(obj);
	node->parent = NULL;
	node->rank = NULL;
	node->tree = NULL;
	((Identifiable*)node)->_type = _NODE_;
	((Identifiable*)node)->_container = _TREE_;
	((Identifiable*)node)->_size = sizeof(Node);	
}

double get_branch_length(SV* obj) {
	return _to_node(obj)->branch_length;
}

void set_branch_length(SV* obj, double length) {
	_to_node(obj)->branch_length = length;
}

AV* get_children(SV* obj) {
	return get_entities(obj);
}

AV* get_ancestors(SV* obj) {
	AV* ret = newAV();
	Node* parent = _to_node(obj)->parent;
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

AV* get_descendants(SV* obj) {
	AV* ret = newAV();	
	_desc(obj, ret);
	return ret;	
}

void set_raw_parent(SV* cobj, SV* pobj) {
	_to_node(cobj)->parent = pobj;
	SvREFCNT_inc(pobj);
}

SV* get_parent(SV* obj) {
	return _to_node(obj)->parent;
}

void set_raw_child(SV* pobj, SV* cobj, ...) {	
	Inline_Stack_Vars;	// handle variable argument list
	
	// determine where to place the child, 
	// default -1 means at the end 
	signed int position = -1;
	if ( Inline_Stack_Items > 2 ) {
		position = SvIV(Inline_Stack_Item(2));
	}	
	
	if ( position == -1 ) {
		insert(pobj, cobj);
	}
	else {
		insert_at_index(pobj,cobj,position);
	}

	Inline_Stack_Void; // handle variable argument list
}

char* get_rank(SV* obj) {
	return _to_node(obj)->rank;
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