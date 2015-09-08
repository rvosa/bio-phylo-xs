#ifndef CHARACTERS_H
#define CHARACTERS_H

# include "src/TypeSafeData.h"

typedef struct {
	TypeSafeData * type;
} Characters;

initialize_characters(Characters* self);

#endif
