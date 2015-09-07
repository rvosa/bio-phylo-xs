# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Writable.h"
# include "src/Listable.h"
# include "src/Node.h"

Node *create(const char *classname) {
	Node *self;
	Newx(self,1,Node);
	((Identifiable*)self)->_class = savepv(classname);
	((Writable*)self)->tag = savepv("node");	
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

Node* set_branch_length(Node* self, double length) {
	self->branch_length = length;
	return self;
}

Node* set_tree(Node* self, Tree* tree) {
	self->tree = tree;
	return self;
}

Tree* get_tree(Node* self) {
	return self->tree;
}

char* get_rank(Node* self) {
	return self->rank;
}

Node* set_rank(Node* self, char * rank) {
	self->rank = savepv(rank);
	return self;
}

Node* set_raw_parent( Node* self, Node* parent ) {
	self->parent = parent;
	return self;
}

Node* get_parent(Node* self) {
	return self->parent;
}

Node* set_raw_child( Node* self, Node* child, ... ) {
	Inline_Stack_Vars;	// handle variable argument list
	
	// determine where to place the child, 
	// default -1 means at the end 
	signed int position = -1;
	if ( Inline_Stack_Items > 2 ) {
		position = SvIV(Inline_Stack_Item(2));
	}
	
	if ( position == -1 ) {
		insert((Listable*)self, (Identifiable*)child);
	}
	else {
		insert_at_index((Listable*)self,(Identifiable*)child,position);
	}
	return self;
}

AV* get_children( Node* self ) {
	return ((Listable*)self)->entities;
}

Node* get_first_daughter( Node* self ) {
	AV* list = ((Listable*)self)->entities;
	if ( av_exists(list,0) ) {
		SV* sv = *(av_fetch(list, 0, 0));
		return (Node*)SvIV(SvRV(sv));
	}
	return NULL;
}

int is_child_of( Node* self, Node* parent ) {
	if ( self->parent != NULL ) {
		return ((Identifiable*)self->parent)->id == ((Identifiable*)parent)->id;
	}
	return 0;
}

int is_ancestor_of( Node* self, Node* desc ) {
	Node* p = desc->parent;
	int sid = ((Identifiable*)self)->id;
	while( p != NULL ) {
		if ( ((Identifiable*)p)->id == sid ) {
			return 1;
		}
		p = p->parent;
	}
	return 0;
}

int is_terminal( Node* self ) {
	return av_len(((Listable*)self)->entities) == 0;
}

int is_internal( Node* self ) {
	return av_len(((Listable*)self)->entities) != 0;
}

int is_root( Node* self ) {
	return self->parent == NULL;
}

void destroy_node(Node* self) {
	destroy_listable((Listable*)self);
}