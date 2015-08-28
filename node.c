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
	return sv_setref_pv(newSViv(0), classname, (void *)node);	
}

double get_branch_length(SV* obj) {
	return ((Node*)SvIV(SvRV(obj)))->branch_length;
}

void set_branch_length(SV* obj, double length) {
	Node* node = (Node*)SvIV(SvRV(obj));
	node->branch_length = length;
}

void set_parent(SV* cobj, SV* parent) {
	Node* child = (Node*)SvIV(SvRV(cobj));
	//Node* parent = (Node*)SvIV(SvRV(pobj));
	child->parent = parent;
}

SV* get_parent(SV* obj) {
	Node* child = (Node*)SvIV(SvRV(obj));
	return child->parent;
}