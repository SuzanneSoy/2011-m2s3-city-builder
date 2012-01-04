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

enum SommetTriangle {
	LEFT = 0,
	TOP = 1,
	RIGHT = 2
};

inline SommetTriangle operator+(SommetTriangle c, int i) {
	return SommetTriangle((((int(c) + int(i)) % 3 ) + 3) % 3);
}

#endif
