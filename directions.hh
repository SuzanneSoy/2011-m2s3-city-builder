#ifndef _DIRECTIONS_HH_
#define _DIRECTIONS_HH_

enum Cardinal {
	N = 0,
	E = 1,
	S = 2,
	W = 3
};

inline Cardinal operator+(Cardinal c, int i) {
	return Cardinal((int(c) + int(i)) & 3);
}

enum Coin {
	NE = 0,
	SE = 1,
	SW = 2,
	NW = 3
};

inline Coin operator+(Coin c, int i) {
	return Coin((int(c) + int(i)) & 3);
}

#endif
