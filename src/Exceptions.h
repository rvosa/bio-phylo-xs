#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

typedef struct {
	char * message;
	char * class_name;
} Exceptions;

SV* except( char * name, char * message );
char* error(SV* self);

#endif
