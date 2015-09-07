# include "src/Writable.h"
# include "src/Identifiable.h"

void initialize_writable(Writable* self){
	initialize_identifiable((Identifiable*)self);
	
	// compose XML id
	char * tag = self->tag;
	int i = 0;
	while( tag[i] != '\0' ) {
		i++;
	}
	char xml_id[10];
	sprintf(xml_id,"%c%c%i",tag[0],tag[i-1],((Identifiable*)self)->id);
	self->xml_id = savepv(xml_id);
	
	// initialize other fields
	self->attributes = newHV();
	self->meta = newAV();
	self->url = NULL;
	self->is_identifiable = 1;
	self->is_suppress_ns = 0;
}

Writable* set_link(Writable* self, char* url) {
	self->url = savepv(url);
	return self;
}

char* get_link(Writable* self) {
	return self->url;
}

Writable* set_name(Writable* self, char* name) {
	hv_store(self->attributes, "label", 5, newSVpv(name,0), 0);
	return self;
}

char* get_name(Writable* self) {
	if ( hv_exists(self->attributes, "label", 5) ) {
        SV* label = *(hv_fetch(self->attributes, "label", 5, 0));
        char * retval = SvPV_nolen(label);
		return retval;		
	}
	else {
		return NULL;
	}
}

Writable* set_suppress_ns(Writable* self) {
	self->is_suppress_ns = 1;
	return self;
}

Writable* clear_suppress_ns(Writable* self) {
	self->is_suppress_ns = 0;
	return self;
}

int is_ns_suppressed(Writable* self) {
	return self->is_suppress_ns;
}

int get_suppress_ns(Writable* self) {
	return self->is_suppress_ns;
}

Writable* set_identifiable(Writable* self, int value) {
	self->is_identifiable = value;
	return self;
}

int is_identifiable(Writable* self) {
	return self->is_identifiable;
}

int get_identifiable(Writable* self) {
	return self->is_identifiable;
}

Writable* set_tag(Writable* self, char * tag ) {
	self->tag = savepv(tag);
	return self;
}

char * get_tag(Writable* self) {
	return self->tag;
}

char * get_xml_id(Writable* self) {
	return self->xml_id;
}