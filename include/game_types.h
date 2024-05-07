#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <game_constants.h>

typedef enum square {
	BLANK = 0,
	X = 1,
	O = -1,
} Square;

typedef int Coordinate[DIMENSIONS];

#endif
