#ifndef _GEOMETRY_DIRECTIONS_HH_
#define _GEOMETRY_DIRECTIONS_HH_

enum Cardinal {
	N = 0,
	E = 1,
	S = 2,
	W = 3
};

inline Cardinal operator+(Cardinal c, int i) {
	return Cardinal((int(c) + int(i)) & 3);
	//int result = int(c) << (i & 3);
	//result = result | result >> 4;
	//return Cardinal (c & 15);
}
inline Cardinal operator-(Cardinal c, int i) {
	return c + (-i);
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
inline Coin operator-(Coin c, int i) {
	return c + (-i);
}

enum SommetTriangle {
	LEFT = 0,
	TOP = 1,
	RIGHT = 2
};

inline SommetTriangle operator+(SommetTriangle c, int i) {
	return SommetTriangle((((int(c) + int(i)) % 3 ) + 3) % 3);
}

inline SommetTriangle operator-(SommetTriangle c, int i) {
	return SommetTriangle((((int(c) - int(i)) % 3 ) + 3) % 3);
}

enum CoteTriangle {
	LEFTSIDE = 0,
	RIGHTSIDE = 1,
	BASE = 2
};

inline CoteTriangle operator+(CoteTriangle c, int i) {
	return CoteTriangle((((int(c) + int(i)) % 3 ) + 3) % 3);
}

inline CoteTriangle operator-(CoteTriangle c, int i) {
	return CoteTriangle((((int(c) - int(i)) % 3 ) + 3) % 3);
}

#endif
