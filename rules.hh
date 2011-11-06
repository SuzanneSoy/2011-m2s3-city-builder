#ifndef _RULES_HH_
#define _RULES_HH_

typedef enum Cardinaux {
	N = 0,
	E = 1,
	S = 2,
	W = 3
} Cardinaux;

typedef enum Diagonales {
	NE = 0,
	SE = 1,
	SW = 2,
	NW = 3
} Diagonales;

typedef struct IO {
	int in;
	int out;
} IO;

#endif
