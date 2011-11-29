#include "all_includes.hh"

Segment::Segment(Vertex u, Vertex v): u(u), v(v) {}

int Segment::length() {
	int x = u.x - v.x;
	int y = u.y - v.y;
	return std::sqrt(x*x + y*y);
}

int Segment::width() {
	return std::abs(u.x - v.x);
}

int Segment::height() {
	return std::abs(u.y - v.y);
}
