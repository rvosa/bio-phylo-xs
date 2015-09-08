#ifndef CHARACTER_H
#define CHARACTER_H

# include "src/TypeSafeData.h"

typedef struct {
	TypeSafeData * type;
} Character;

initialize_character(Character* self);

#endif
