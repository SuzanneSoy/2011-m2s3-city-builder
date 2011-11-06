#include "vertex.hh"

Vertex::Vertex() {}

Vertex::Vertex(int x, int y): x(x), y(y) {}

Vertex Vertex::add(int dx, int dy) {
	Vertex v = *this;
	v.x += dx;
	v.y += dy;
	return v;
}

std::ostream& operator<<(std::ostream& os, const Vertex& v) {
	return os << "(" << v.x << "," << v.y << ")";
}
