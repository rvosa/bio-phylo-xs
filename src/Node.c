# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Node.h"

Node *new(const char *classname) {
    Node *self;
    Newx(self,1,Node);
    ((Identifiable*)self)->_class = savepv(classname);
    initialize_node(self);
    return self;
}

void initialize_node(Node* self) {
	initialize_listable((Listable*)self);
	self->parent = NULL;
	self->rank = NULL;
	self->tree = NULL;
	self->branch_length = 0.0;
	((Identifiable*)self)->_type = _NODE_;
	((Identifiable*)self)->_container = _TREE_;
}

double get_branch_length(Node* self) {
	return self->branch_length;
}

void set_branch_length(Node* self, double length) {
	self->branch_length = length;
}

char* get_rank(Node* self) {
	return self->rank;
}

void set_rank(Node* self, char * rank) {
	self->rank = savepv(rank);
}

Node* set_raw_parent( Node* self, Node* parent ) {
    self->parent = parent;
    return self;
}

Node* get_parent(Node* self) {
    return self->parent;
}

Node* set_raw_child( Node* self, Node* child ) {
	insert((Listable*)self,(Identifiable*)child);
	return self;
}

AV* get_children( Node* self ) {
	return ((Listable*)self)->entities;
}

void destroy_node(Node* self) {
	destroy_listable((Listable*)self);
	if ( self->rank != NULL ) {
		Safefree(self->rank);
	}
}