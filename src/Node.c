# include "src/types.h"
# include "src/Identifiable.h"
# include "src/Listable.h"
# include "src/Node.h"

/*
// this is the reference (perlref)
SV = RV(0x10082e008) at 0x10082dff8
  REFCNT = 1
  FLAGS = (PADMY,ROK)
  RV = 0x100804ed0
  
  // this is the blessed object (obj_ref)
  SV = PVMG(0x1009e5cc0) at 0x100804ed0
    REFCNT = 1
    FLAGS = (OBJECT,IOK,READONLY,pIOK)
    IV = 4313962048
    NV = 0
    PV = 0
    STASH = 0x10085af88 "Bio::PhyloXS::Forest::Node"
*/

Node* create(const char * classname) {
    Node *self;

    /* allocate and initialize struct */
    Newx(self, 1, Node);
    initialize_node(self);

    /* create perl object and ref; store pointer to object in struct */
    SV* perlref = newSViv((IV)self);
    SV* obj_ref = newRV_noinc(perlref);
    sv_bless(obj_ref, gv_stashpv(classname, TRUE));
    SvREADONLY_on(perlref);
    ((Identifiable*)self)->sv = obj_ref;
	((Identifiable*)self)->ref = perlref;
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
	((Identifiable*)self)->_size = sizeof(Node);	
}

double get_branch_length(Node* self) {
	return self->branch_length;
}

void set_branch_length(Node* self, double length) {
	self->branch_length = length;
}

AV* get_children(Node* self) {
	return get_entities((Listable*)self);
}

AV* get_ancestors(Node* self) {
	AV* ret = newAV();
	Node* parent = self->parent;
	while(parent != NULL) {
		av_push(ret, ((Identifiable*)parent)->sv);
		parent = parent->parent;
	}
	return ret;
}

void _desc(Node* parent, AV* set);

void _desc(Node* parent, AV* set) {
	Listable* pl = (Listable*)parent;
	int i;
	for ( i = 0; i < pl->used; i++ ) {
		Node* child = (Node*)pl->entities[i];
		av_push(set, ((Identifiable*)child)->sv);
		_desc(child, set);
	}	
}

Node* get_first_daughter(Node* self) {
	Listable* pl = (Listable*)self;
	if ( pl->used > 0 ) {
		return (Node*)pl->entities[0];
	}
	else {
		return NULL;
	}
}

int is_terminal(Node* self) {
	return ((Listable*)self)->used == 0;
}

AV* get_descendants(Node* self) {
	AV* ret = newAV();	
	_desc(self, ret);
	return ret;	
}

void _ido(Node* parent, int *tf, int id);

void _ido(Node* parent, int *tf, int id) {
	Listable* pl = (Listable*)parent;
	int i;
	for ( i = 0; i < pl->used; i++ ) {
		Node* child = (Node*)pl->entities[i];
		if ( ((Identifiable*)child)->id == id ) {
			*tf = 1;
			break;
		}
		_ido(child, tf, id);
	}	
}

// tests if invocant is descendant of argument
int is_descendant_of(Node* self, Node* other) {
	int id = ((Identifiable*)self)->id;
	int ret = 0;
	_ido(other,&ret,id);
	return ret;
}

Node* set_raw_parent(Node* self, Node* parent) {
	self->parent = parent;
	SvREFCNT_inc(((Identifiable*)parent)->sv);
	return parent;
}

Node* get_parent(Node* self){
	if ( self->parent != NULL ) {
		SvREFCNT_inc(((Identifiable*)self->parent)->sv);
	}
	return self->parent;
}

void set_raw_child(Node* self, Node* child, ...) {	
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

	Inline_Stack_Void; // handle variable argument list
}

char* get_rank(Node* self) {
	return self->rank;
}

void set_rank(Node* self, char * rank) {
	self->rank = savepv(rank);
}

Tree* get_tree(Node* self) {
	return self->tree;
}

void set_tree(Node* self, Tree* tree) {
	self->tree = tree;
}

void destroy_node(Node* self) {
	destroy_listable((Listable*)self);
	Safefree(self->rank);
	Safefree(self);
}