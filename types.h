#ifndef TYPES_H
#define TYPES_H

typedef struct {
     char* name;
     int legs;
} Animal;

typedef struct {
	Animal animal;
	char* owner;
} Cat;

#endif