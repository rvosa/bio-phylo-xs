# include "src/Writable.h"
# include "src/Identifiable.h"

void initialize_writable(Writable* self){
	initialize_identifiable((Identifiable*)self);
	self->attributes = newHV();
	self->meta = newAV();
	self->url = NULL;
	self->is_identifiable = 1;
	self->is_suppress_ns = 0;
}

Writable* set_attributes(Writable* self, ...) {
	Inline_Stack_Vars;	// handle variable argument list
	
	// get either a hash ref or key/value pairs
	HV* newValues;
	if ( Inline_Stack_Items == 2 ) {
		newValues = (HV*)SvRV(Inline_Stack_Item(1));
	}
	else {
		newValues = newHV();
		int i;
		for ( i = 1; i < Inline_Stack_Items - 1; i += 2 ) {
			SV* key = Inline_Stack_Item(i);
			SV* value = Inline_Stack_Item(i+1);
			char* keystr = SvPV_nolen(key);
			hv_store(newValues, keystr, strlen(keystr), value, 0);
		}
	}
	
	// iterate over keys
	I32 keys = hv_iterinit(newValues);
	I32 i;
	for ( i = 0; i < keys; i++ ) {
		char * key = NULL;
		I32 key_length = 0;
		SV* value = hv_iternextsv(newValues, &key, &key_length);		
		
		// verify namespace prefixes
		char * pch = strchr( key, ':' );
		if ( pch != NULL ) {
			int pos = pch - key;
			char * prefix = (char*) malloc(pos);
			strncpy( prefix, key, pos );			
			char * msg = "Unbound attribute prefix '%s'\n";
			
			// should use logger, and should be conditional on:
			// 1. it not being 'xmlns',
			// 2. it not being known in global set of namespaces			
			printf(msg,prefix);
		}
		
		// store value
		hv_store(self->attributes, key, strlen(key), value, 0);
	}

	return self;
}

HV* get_attributes(Writable* self) {
	return self->attributes;
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

const char * get_tag(Writable* self) {
	int idx = ((Identifiable*)self)->_index;
	return tag[idx];
}

char * get_xml_id(Writable* self) {
	char xml_id[10];
	int idx = ((Identifiable*)self)->_index;
	int end_idx = strlen(tag[idx]) - 1;	
	char start = tag[idx][0];
	char end = tag[idx][end_idx];
	sprintf(xml_id,"%c%c%d",start,end,((Identifiable*)self)->id);
	return xml_id;
}

Writable* set_base_uri(Writable* self, char * uri) {
	hv_store(self->attributes, "xml:base", 8, newSVpv(uri,0), 0);	
	return self;
}

void destroy_writable(Writable* self) {
	destroy_identifiable((Identifiable*)self);
//	SvREFCNT_dec(self->attributes);
//	SvREFCNT_dec(self->meta);
	if ( self->url != NULL ) {
		Safefree(self->url);	
	}
}