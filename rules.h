#include <iostream>

typedef struct Vertex {
	int x;
	int y;
	//int z;
	Vertex() {}
	Vertex(int x, int y): x(x), y(y) {}
	Vertex add(int dx, int dy) { Vertex v = *this; v.x += dx; v.y += dy; return v; }
} Vertex;
std::ostream& operator<<(std::ostream& os, const Vertex& v);

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
