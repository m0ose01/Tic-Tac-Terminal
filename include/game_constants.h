#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED

typedef enum square {
	BLANK = 0,
	X = 1,
	O = -1,
} Square;

#define DIMENSIONS 2
typedef int Coordinate[DIMENSIONS];

#define MAX_LINELENGTH 50
#define MIN_BOARD_SIZE 3
#define MAX_BOARD_SIZE 100

#define CURSOR_COLOUR 1

#endif
