/*
Allocate memory with Newx if it's
available - if it's an older perl
that doesn't have Newx then we
resort to using New.
*/
#ifndef Newx
#  define Newx(v,n,t) New(0,v,n,t)
#endif
    
# include "types.h"

SV* create(const char * classname) {
	Node * node;
	Newx(node, 1, Node);
	node->first_daughter = NULL;
	node->parent         = NULL;
	node->next_sister    = NULL;
	return sv_setref_pv(newSViv(0), classname, (void *)node);	
}

double get_branch_length(SV* obj) {
	return ((Node*)SvIV(SvRV(obj)))->branch_length;
}

void set_branch_length(SV* obj, double length) {
	Node* node = (Node*)SvIV(SvRV(obj));
	node->branch_length = length;
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

AV* get_children(SV* obj) {
	AV* ret = newAV();
	Node* child = _to_node(obj)->first_daughter;
	while(child != NULL) {
		SV* svc = _to_sv(child);
		SvREFCNT_inc(svc);
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
		SvREFCNT_inc(svp);
		av_push(ret, svp);
		parent = parent->parent;
	}
	return ret;
}

AV* get_descendants(SV* obj) {
	AV* ret = newAV();
	Node* child = _to_node(obj)->first_daughter;
	_desc(child, ret);
	return ret;	
}

void _desc(Node* node, AV* set) {
	Node* fd = node->first_daughter;
	while(node != NULL) {
		SV* svn = _to_sv(node);
		SvREFCNT_inc(svn);
		av_push(set, svn);
		node = node->next_sister;
		_desc(node, set);
	}
	while(fd != NULL) {
		SV* svd = _to_sv(fd);
		SvREFCNT_inc(svd);
		av_push(set, svd);
		fd = fd->first_daughter;
		_desc(fd, set);
	}	
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

void set_raw_child(SV* pobj, SV* cobj) {
	Node* prev  = _to_node(pobj)->first_daughter;
	Node* child = _to_node(cobj);
	if ( prev != NULL ) {	
		while( prev->next_sister != NULL ) {
			prev = prev->next_sister;
		}
		prev->next_sister = child;
	}
	else {
		_to_node(pobj)->first_daughter = child;
	}
	SvREFCNT_inc(cobj);
}