# include "types.h"
# include "identifiable.h"
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
	node->first_daughter = NULL;
	node->parent         = NULL;
	node->next_sister    = NULL;
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
	AV* ret = newAV();
	Node* child = _to_node(obj)->first_daughter;
	while(child != NULL) {
		SV* svc = _to_sv(child);
		av_push(ret, svc);
		child = child->next_sister;
	}
	return ret;
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

void _desc(Node* node, AV* set);

void _desc(Node* node, AV* set) {
	Node* fd = node->first_daughter;
	while(node != NULL) {
		SV* svn = _to_sv(node);
		av_push(set, svn);
		node = node->next_sister;
		_desc(node, set);
	}
	while(fd != NULL) {
		SV* svd = _to_sv(fd);
		av_push(set, svd);
		fd = fd->first_daughter;
		_desc(fd, set);
	}	
}

AV* get_descendants(SV* obj) {
	AV* ret = newAV();
	Node* child = _to_node(obj)->first_daughter;
	_desc(child, ret);
	return ret;	
}

void set_next_sister(SV* obj, SV* sobj) {
	_to_node(obj)->next_sister = _to_node(sobj);
	SvREFCNT_inc(sobj);
}

SV* get_next_sister(SV* obj) {
	return _to_sv(_to_node(obj)->next_sister);
}

void set_first_daughter(SV* pobj, SV* cobj) {
	_to_node(pobj)->first_daughter = _to_node(cobj);
	SvREFCNT_inc(cobj);
}

SV* get_first_daughter(SV* obj) {
	return _to_sv(_to_node(obj)->first_daughter);
}

void set_raw_parent(SV* cobj, SV* pobj) {
	_to_node(cobj)->parent = _to_node(pobj);
	SvREFCNT_inc(pobj);
}

SV* get_parent(SV* obj) {
	return _to_sv(_to_node(obj)->parent);
}

void set_raw_child(SV* pobj, SV* cobj, ...) {	
	Inline_Stack_Vars;	// handle variable argument list
	
	// determine where to place the child, 
	// default -1 means at the end 
	signed int position = -1;
	if ( Inline_Stack_Items > 2 ) {
		position = SvIV(Inline_Stack_Item(2));
	}	
	
	// convert objects
	Node* prev  = _to_node(pobj)->first_daughter;
	Node* child = _to_node(cobj);
	
	// find previous sister
	if ( prev != NULL ) {	
		int i = 0;
		while( prev->next_sister != NULL ) {
			if ( position != -1 && i == position ) {
				break;
			}
			prev = prev->next_sister;
			i++;
		}
		Node* prevsis = prev->next_sister;
		prev->next_sister = child;
		child->next_sister = prevsis;
	}
	else {
		_to_node(pobj)->first_daughter = child;
	}
	SvREFCNT_inc(cobj);	
	Inline_Stack_Void; // handle variable argument list
}
